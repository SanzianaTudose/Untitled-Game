// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityObjectComponent.h"
#include "ElementInteractionManager.h"
#include "EnemyCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UAbilityObjectComponent::UAbilityObjectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilityObjectComponent::BeginPlay()
{
	Super::BeginPlay();
	//get collision object and add OnEnemyHit as the overlap event
	TArray<UStaticMeshComponent*> StaticMeshComps;
	GetOwner()->GetComponents(StaticMeshComps);

	if(StaticMeshComps.Num() > 0)
	{
		MainObj = StaticMeshComps[0];
		MainObj->OnComponentBeginOverlap.AddDynamic(this, &UAbilityObjectComponent::OnEnemyHit);
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find component!"));
	}

	//save the initial position for range calculations
	InitialPosition = GetOwner()->GetActorLocation();
	// ...
	
}


// Called every frame
void UAbilityObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector CurrentPosition = GetOwner()->GetActorLocation();

	//if range is exeeded destroy the object
	float Distance = FVector::Dist(InitialPosition, CurrentPosition);
	if(Distance > Range)
	{
		//delete object
		UE_LOG(LogTemp, Display, TEXT("Object out of range: %f / %f"), Distance, Range);
		GetOwner()->Destroy();
	}
	// ...
}

void UAbilityObjectComponent::OnEnemyHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, MyOwner, DamageTypeClass);

	AEnemyCharacter* enemy = dynamic_cast<AEnemyCharacter*>(OtherActor);
	if(enemy)
	{
		AElementInteractionManager::AbilityEnemyInteract(Element, enemy->Status, SweepResult.ImpactPoint, OtherActor);
		enemy->UpdateStatus(Element);
	}
}

void UAbilityObjectComponent::SetData(float d, bool doh, float r)
{
	//set all the needed variables
	//element
	//effect[]
	Damage = d;
	bDestroyOnHit = doh;
	Range = r;
}