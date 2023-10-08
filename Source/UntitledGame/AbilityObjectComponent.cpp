// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityObjectComponent.h"

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
		UStaticMeshComponent* Comp = StaticMeshComps[0];
		Comp->OnComponentBeginOverlap.AddDynamic(this, &UAbilityObjectComponent::OnEnemyHit);
		UE_LOG(LogTemp, Warning, TEXT("Found component!"));

	}else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find component!"));
	}

	//save the initial position for range calculations
	initialPosition = GetOwner()->GetActorLocation();
	// ...
	
}


// Called every frame
void UAbilityObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector currentPosition = GetOwner()->GetActorLocation();

	//if range is exeeded destroy the object
	float distance = FVector::Dist(initialPosition, currentPosition);
	if(distance > range)
	{
		//delete object
		GetOwner()->Destroy();
	}
	// ...
}

void UAbilityObjectComponent::OnEnemyHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Collision detected"));
}


