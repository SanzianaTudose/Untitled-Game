// Fill out your copyright notice in the Description page of Project Settings.


#include "SmiteAbilityObjectComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyCharacter.h"

void USmiteAbilityObjectComponent::BeginPlay()
{
	Super::BeginPlay();
    
}

void USmiteAbilityObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    TArray<FOverlapResult> OutOverlaps;
    FCollisionObjectQueryParams LootObjectQueryParams;
    FCollisionShape CollisionShape;

    LootObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
    CollisionShape.SetSphere(400.0f);
    AActor* Owner = GetOwner();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(Owner->GetWorld(), 0);
    Owner->GetWorld()->OverlapMultiByObjectType(OutOverlaps, Owner->GetActorLocation(), Owner->GetActorQuat(), LootObjectQueryParams, CollisionShape);
    for(FOverlapResult res : OutOverlaps)
    {
        if(res.GetActor() == PlayerPawn)
        {
            continue;
        }
        OnSmiteHit(res.GetActor(), res.GetActor()->GetActorLocation());
    }
    UE_LOG(LogTemp, Warning, TEXT("Collision %d"), OutOverlaps.Num());
    SetComponentTickEnabled(false);
}

void USmiteAbilityObjectComponent::OnSmiteHit(AActor* OtherActor, FVector hitPoint)
{
	UE_LOG(LogTemp, Display, TEXT("Collision detected"));

	auto MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AUntitledGameProjectile: Owner is null."));
		return;
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();
	// Make sure not to damage self or projectile owner
	if (OtherActor && OtherActor != MyOwner)
    {
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, MyOwner, DamageTypeClass);
    }
	AEnemyCharacter* enemy = dynamic_cast<AEnemyCharacter*>(OtherActor);
	if(enemy)
	{
		EIM->AbilityEnemyInteract(Element,enemy->Status, hitPoint, OtherActor);
		enemy->UpdateStatus(Element);
	}
}