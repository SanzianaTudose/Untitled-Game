// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	// Bind callback function (UHealthComponent::DamageTaken) to OnTakeAnyDamage delegate
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	float DamageToApply = FMath::Min(Health, Damage);
	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("%s health : % f"), *GetOwner()->GetName(), Health);

	if (Health <= 0.f)
	{
		// TODO: Handle death
	}
}


