// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UntitledGameProjectile.h"
#include "Blueprint/UserWidget.h"
#include "Component.h"
#include "PlayerCursorManager.h"
#include "Components/DecalComponent.h"

#include "WeaponCore.generated.h"


UCLASS(ClassGroup = (WeaponSystem), meta = (BlueprintSpawnableComponent))
class UNTITLEDGAME_API UWeaponCore : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponCore();

	// base stats 
	UPROPERTY(Category = WeaponSystem, EditAnywhere, BlueprintReadWrite)
	TMap<WeaponStat, float> Stats{
		{WeaponStat::MaxAbilities, 0.0f}, // Should be an integer!
		{WeaponStat::FireRate, 0.0f},
		{WeaponStat::ReloadTime, 0.0f}
	};

	// shooting variables
	UPROPERTY(Category = WeaponSystem, EditAnywhere, BlueprintReadWrite)
	float CurrentReloadTimeLeft;
	bool bCanFire;
	void ShotTimerExpired();
	void OnFire();
	FORCEINLINE void SetCursorManager(class UPlayerCursorManager* NewCursorManager)
	{
		CursorManager = NewCursorManager;
	}

	// Ability functions
#pragma region Abilities
	UFUNCTION(BlueprintCallable)
	void GenerateStats(int level);
	UFUNCTION(BlueprintCallable)
	void AddAbility(TSubclassOf<AActor> AbilityClass);
	void RemoveAbility(AUntitledGameProjectile* Ability);
	void ActivateAbility(FVector SpawnLocation, FRotator SpawnRotation);
#pragma endregion Abilities

	// Component functions
#pragma region Components
	UFUNCTION(BlueprintCallable)
	void AddComponent(UComponent* Component);
	void RemoveComponent(UComponent* Component);

	// Updates current WeaponCore stats. {isAdded} - indicates if the Component modifiers should be added or removed
	void ApplyComponentModifiers(UComponent* Component, bool isAdded);
#pragma endregion Components

	// Shooting functions
	AActor* OwningActor;
	/** Offset from the player location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FVector GunOffset;
	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

private:
	int PlayerLevel;
	int AbilityIndex;
	TArray<TSubclassOf<AActor>> AbilitiesClasses;
	FTimerHandle TimerHandle_ReloadTimeDecrement;

	UPROPERTY(Category = WeaponSystem, VisibleAnywhere)
	TSet<UComponent*> Components;

	void DecrementReloadTime();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UPlayerCursorManager* CursorManager;

};
