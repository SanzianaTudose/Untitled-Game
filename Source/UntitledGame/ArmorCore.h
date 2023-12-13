// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArmorCoreDA.h"

#include "ArmorCore.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNTITLEDGAME_API UArmorCore : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UArmorCore();

	UPROPERTY(Category = ArmorSystem, EditAnywhere, BlueprintReadWrite)
	TMap<ArmorStat, float> Stats{
		{ArmorStat::Health, 0.f},
		{ArmorStat::MovementSpeed, 0.f}
	};

	// Data asset holding the base stats used to initialize this ArmorCore
	UPROPERTY(Category = ArmorSystem, EditAnywhere, BlueprintReadWrite)
	UArmorCoreDA* BaseArmorCore;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Initializes {Stats} TMap based on {BaseArmorCore}
	void InitializeCoreStats();
};
