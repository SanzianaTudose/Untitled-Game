// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponCore.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include <iostream>
#include <random>

UWeaponCore::UWeaponCore()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}

void UWeaponCore::BeginPlay()
{
	Super::BeginPlay();
	AbilityIndex = 0;
	AbilitiesClasses = TArray<TSubclassOf<AActor>>();
	AbilitiesClasses.Add(AUntitledGameProjectile::StaticClass());
	bCanFire = true;
}

void UWeaponCore::GenerateStats(int level)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	MaxAbilities = 1;
	std::uniform_real_distribution<> dis(1.0f, 2.0f);
	FireRate = dis(gen);
	std::uniform_real_distribution<> dis2(1.0f, 3.0f);
	ReloadTime = dis2(gen);
}


void UWeaponCore::AddAbility(TSubclassOf<AActor> AbilityClass)
{
	AbilitiesClasses.Add(AbilityClass);

	// Remove first item if array is too big TODO: make this behavior clear to the Player, maybe call RemoveAbility() ?
	if (AbilitiesClasses.Num() > MaxAbilities)
	{
		AbilitiesClasses.RemoveAt(0, 1, true);
	}
}

void UWeaponCore::RemoveAbility(AUntitledGameProjectile* Ability)
{

}

void UWeaponCore::ActivateAbitlity(FVector SpawnLocation, FRotator SpawnRotation, AActor* OwningActor)
{
	if (!bCanFire || AbilitiesClasses.Num() == 0) return;

	UWorld* World = GetWorld();
	if (!World) return; // Make sure GetWorld() doesn't return nullptr.

	AActor* NewProjectile = World->SpawnActor<AActor>(AbilitiesClasses[AbilityIndex], SpawnLocation, SpawnRotation);
	NewProjectile->SetOwner(OwningActor);
	bCanFire = false;

	FTimerHandle TimerHandle_ShotTimerExpired;
	float TimerDuration = (AbilityIndex == AbilitiesClasses.Num() - 1) ? ReloadTime : FireRate;

	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &UWeaponCore::ShotTimerExpired, TimerDuration);

	AbilityIndex++;
	AbilityIndex = AbilityIndex % AbilitiesClasses.Num();
    if(AbilityIndex == AbilitiesClasses.Num() - 1)
    {
        CurrentReloadTimeLeft = ReloadTime;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReloadTimeDecrement, this, &UWeaponCore::DecrementReloadTime, 0.1f, true);
    }
    else
    {
        CurrentReloadTimeLeft = FireRate;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReloadTimeDecrement, this, &UWeaponCore::DecrementReloadTime, 0.1f, true);
    }
}

void UWeaponCore::ShotTimerExpired()
{
	bCanFire = true;
}




void UWeaponCore::DecrementReloadTime()
{
    CurrentReloadTimeLeft -= 0.1; // Decrement the time by the frame time.


    // If the reload time has expired, stop updating.
    if(CurrentReloadTimeLeft <= 0.0f)
    {
        GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ReloadTimeDecrement);
        ShotTimerExpired();
    }
}