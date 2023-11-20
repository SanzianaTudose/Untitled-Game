#include "ItemSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"


// Sets default values
AItemSpawner::AItemSpawner()
{
    // Initialization code...
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
    Super::BeginPlay();
	SpawnItem();

}

void AItemSpawner::SpawnItem()
{
	FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    FVector Location = GetActorLocation();
    FRotator Rotation = GetActorRotation();

    if (ItemType == ItemType::Ability && AbilityItemBlueprint)
	{
		AActor* SpawnedAbility = GetWorld()->SpawnActor<AActor>(AbilityItemBlueprint, Location, Rotation, SpawnParams);
		SpawnedAbility->SetOwner(this);
		if (SpawnedAbility)
		{
			UClass* ActorClass = SpawnedAbility->GetClass();

			if (UObjectProperty* AbilityClassProp = FindField<UObjectProperty>(ActorClass, FName("AbilityClass")))
			{
				AActor* CurrentAbilityClassValue = Cast<AActor>(AbilityClassProp->GetObjectPropertyValue_InContainer(SpawnedAbility));
				AbilityClassProp->SetObjectPropertyValue_InContainer(SpawnedAbility, AbilityType);
			}
		}
	}
    else if (ItemType == ItemType::WeaponCore && WeaponItemDebugBlueprint)
    {
        AActor* SpawnedWeapon = GetWorld()->SpawnActor<AActor>(WeaponItemDebugBlueprint, Location, Rotation, SpawnParams);
		SpawnedWeapon->SetOwner(this);
        if (SpawnedWeapon)
        {
            UWeaponCore* WeaponCoreComponent = Cast<UWeaponCore>(SpawnedWeapon->GetComponentByClass(UWeaponCore::StaticClass()));
            if (WeaponCoreComponent && !RandomizeStats)
            {
                // Setting static stats if RandomizeStats is false
                WeaponCoreComponent->FireRate = FireRate;
                WeaponCoreComponent->ReloadTime = ReloadTime;
                WeaponCoreComponent->MaxAbilities = MaxAbility;
            }

            UClass* ActorClass = SpawnedWeapon->GetClass();

            if (UBoolProperty* RandomizeStatsProp = FindField<UBoolProperty>(ActorClass, FName("RandomizeStats")))
            {
                UE_LOG(LogTemp, Warning , TEXT("RandomizeStatsProp found"));
                RandomizeStatsProp->SetPropertyValue_InContainer(SpawnedWeapon, RandomizeStats);
                OnItemSpawned.Broadcast();
            }
        }
    }
}

void AItemSpawner::RespawnItem()
{
    FTimerHandle UnusedHandle;
    GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AItemSpawner::SpawnItem, 5.0f, false);
}

