// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorCore.h"
#include "PlayerCharacter.h"

UArmorCore::UArmorCore()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UArmorCore::BeginPlay()
{
	Super::BeginPlay();

	

	InitializeCoreStats();
}

void UArmorCore::InitializeCoreStats()
{
	if (!BaseArmorCore)
	{
		UE_LOG(LogTemp, Error, TEXT("ArmorCore: Cannot find Base Armor Core!"));
		return;
	}

	for (TPair<ArmorStat, float> Stat : BaseArmorCore->Stats)
		Stats.Emplace(Stat.Key, Stat.Value);
}

#pragma region Components

void UArmorCore::AddComponent(UComponent* Component)
{
	if (!Component) return;

	if (Components.Contains(Component))
	{
		UE_LOG(LogTemp, Warning, TEXT("ArmorCore: Component cannot be added twice!"));
		return;
	}

	ApplyComponentModifiers(Component, true);
	Components.Add(Component);
}

// TODO: TEST THIS METHOD!
void UArmorCore::RemoveComponent(UComponent* Component)
{
	if (!Component) return;

	if (!Components.Contains(Component))
	{
		UE_LOG(LogTemp, Warning, TEXT("ArmorCore: Cannot remove Component that has not been already added!"));
		return;
	}

	ApplyComponentModifiers(Component, false);
	Components.Remove(Component);
}

void UArmorCore::ApplyComponentModifiers(UComponent* Component, bool isAdded)
{
	float Sign = (isAdded ? 1 : -1);
	for (TPair<ArmorStat, float> Modifier : Component->ArmorModifiers)
		Stats.Emplace(Modifier.Key, Stats[Modifier.Key] + Sign * Modifier.Value);

	APlayerCharacter* PlayerOwner = Cast<APlayerCharacter>(GetOwner());
	if (PlayerOwner)
		PlayerOwner->ApplyArmorStats();
}

#pragma region Components