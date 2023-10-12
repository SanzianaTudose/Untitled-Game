// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponCore.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include <iostream>
#include <random>

// Sets default values
AWeaponCore::AWeaponCore()
{

}

// Called when the game starts or when spawned
void AWeaponCore::BeginPlay()
{
	Super::BeginPlay();
	AbilityIndex = 0;
	AbilitiesClasses = TArray<TSubclassOf<AUntitledGameProjectile>>();
	AbilitiesClasses.Add(AUntitledGameProjectile::StaticClass());
	bCanFire = true;
}

void AWeaponCore::GenerateStats(int level)
{
	int MaxAbilities = 1;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(1.0, 2.0);
	float FireRate = dis(gen);
	std::uniform_real_distribution<> dis2(1.0, 3.0);
	float ReloadTime = dis2(gen);
}

void AWeaponCore::AddAbility(AUntitledGameProjectile* Ability)
{

}

void AWeaponCore::RemoveAbility(AUntitledGameProjectile* Ability)
{

}

void AWeaponCore::ActivateAbitlity( FVector SpawnLocation, FRotator SpawnRotation)
{
	if (!bCanFire) return;
	UWorld* World = GetWorld();
	AUntitledGameProjectile* NewProjectile = GetWorld()->SpawnActor<AUntitledGameProjectile>(AbilitiesClasses[AbilityIndex], SpawnLocation, SpawnRotation);
	bCanFire = false;
	FTimerHandle TimerHandle_ShotTimerExpired;
	if (AbilityIndex == AbilitiesClasses.Num() - 1)
	{
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AWeaponCore::ShotTimerExpired, ReloadTime);
	}else{
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AWeaponCore::ShotTimerExpired, FireRate);
	}
	AbilityIndex++;
	AbilityIndex = AbilityIndex % AbilitiesClasses.Num();
}

void AWeaponCore::ShotTimerExpired()
{
	bCanFire = true;
}

