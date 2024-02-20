// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Component.generated.h"

UENUM(BlueprintType)
enum class WeaponStat : uint8
{
	MaxAbilities, // TODO: Components should not be able to modify MaxAbilities!
	FireRate,
	ReloadTime
};

UENUM(BlueprintType)
enum class ComponentType : uint8
{
	Stock,
	Barrel,
	Sight,
	Trigger,
};

/**
 *  Holds information about a generic component and the stats it modifies.
 */
UCLASS(BlueprintType)
class UNTITLEDGAME_API UComponent : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ComponentType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<WeaponStat, float> Modifiers;
};