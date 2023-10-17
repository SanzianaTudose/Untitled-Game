// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UntitledGameProjectile.h"
#include "WeaponCore.generated.h"


UCLASS( ClassGroup=(WeaponSystem), meta=(BlueprintSpawnableComponent) )
class UNTITLEDGAME_API UWeaponCore : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponCore();

	UPROPERTY(Category = WeaponSystem, EditAnywhere, BlueprintReadWrite )
	int MaxAbilities;
	UPROPERTY(Category = WeaponSystem, EditAnywhere, BlueprintReadWrite )
	float FireRate;
	UPROPERTY(Category = WeaponSystem, EditAnywhere, BlueprintReadWrite )
	float ReloadTime;
	bool bCanFire;

	UFUNCTION(BlueprintCallable)
	void GenerateStats(int level);
	void AddAbility(AUntitledGameProjectile* Ability);
	void RemoveAbility(AUntitledGameProjectile* Ability);
	void ActivateAbitlity(FVector SpawnLocation, FRotator SpawnRotation);
	void ShotTimerExpired();

private:
	int PlayerLevel;
	int AbilityIndex;
	TArray<TSubclassOf<AUntitledGameProjectile>> AbilitiesClasses;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
