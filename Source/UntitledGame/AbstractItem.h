// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbstractItem.generated.h"

UENUM(BlueprintType)
enum class TypeOfItem : uint8
{
	Weapon,
	Armor,
	Ability,
	Sight,
	Trigger,
	Barrel,
	Stock,
};

UCLASS()
class UNTITLEDGAME_API UAbstractItem : public UDataAsset
{
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TypeOfItem ItemType;
	
};
