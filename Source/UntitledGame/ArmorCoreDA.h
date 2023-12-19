// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ArmorCoreDA.generated.h"

UENUM(BlueprintType)
enum class ArmorStat : uint8
{
	Health,
	MovementSpeed
};

/**
 *  Holds information about a generic Armor Core and its base stats.
 */
UCLASS(BlueprintType)
class UNTITLEDGAME_API UArmorCoreDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ArmorStat, float> Stats = {
		{ArmorStat::Health, 150.f},
		{ArmorStat::MovementSpeed, 600.f}
	};
};
