// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UntitledGameProjectile.h"
#include "Blueprint/UserWidget.h"
#include "Component.h"

#include "WeaponCore.generated.h"


UCLASS(ClassGroup = (WeaponSystem), meta = (BlueprintSpawnableComponent))
class UNTITLEDGAME_API UWeaponCore : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponCore();

	UPROPERTY(Category = WeaponSystem, EditAnywhere, BlueprintReadWrite)
	TMap<WeaponStat, float> Stats{
		{WeaponStat::MaxAbilities, 0.0f}, // Should be an integer!
		{WeaponStat::FireRate, 0.0f},
		{WeaponStat::ReloadTime, 0.0f}
	};

	UPROPERTY(Category = WeaponSystem, EditAnywhere, BlueprintReadWrite)
	float CurrentReloadTimeLeft;
	bool bCanFire;

	UFUNCTION(BlueprintCallable)
	void GenerateStats(int level);
	UFUNCTION(BlueprintCallable)
	void AddAbility(TSubclassOf<AActor> AbilityClass);
	void RemoveAbility(AUntitledGameProjectile* Ability);
	void ActivateAbitlity(FVector SpawnLocation, FRotator SpawnRotation, AActor* OwningActor);
	void ShotTimerExpired();


private:
	int PlayerLevel;
	int AbilityIndex;
	TArray<TSubclassOf<AActor>> AbilitiesClasses;
	FTimerHandle TimerHandle_ReloadTimeDecrement;

	void DecrementReloadTime();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
