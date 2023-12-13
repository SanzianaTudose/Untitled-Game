// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorCore.h"

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