// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbstractItem.h"
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

UCLASS(BlueprintType)
class UNTITLEDGAME_API UComponent : public UAbstractItem
{
	GENERATED_BODY()
	UComponent();
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ComponentType componentType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<WeaponStat, float> Modifiers;
};