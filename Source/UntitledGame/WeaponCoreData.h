// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractItem.h"
#include "Component.h"
#include "WeaponCoreData.generated.h"

/**
 * 
 */
UCLASS()
class UNTITLEDGAME_API UWeaponCoreData : public UAbstractItem
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = WeaponSystem, EditAnywhere, BlueprintReadWrite)
	TMap<WeaponStat, float> Stats{
		{WeaponStat::MaxAbilities, 0.0f}, // Should be an integer!
		{WeaponStat::FireRate, 0.0f},
		{WeaponStat::ReloadTime, 0.0f}
	};
	
};
