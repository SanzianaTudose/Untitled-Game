// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Component.generated.h"

UENUM(BlueprintType)
enum class WeaponStat : uint8
{
	MaxAbilities,
	FireRate,
	ReloadTime
};

USTRUCT(BlueprintType)
struct FStatModifier
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	WeaponStat Stat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Modifier;
};

/**
 *  Holds information about a generic component and the stats it modifies.
 */
UCLASS()
class UNTITLEDGAME_API UComponent : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FStatModifier> Modifiers;
};
