// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootingController.generated.h"


// Attached to the Player Blueprint 

UCLASS(ClassGroup = (WeaponSystem), meta = (BlueprintSpawnableComponent))
class UNTITLEDGAME_API UShootingController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UShootingController();

	void OnFire();

	FORCEINLINE void SetCursorManager(class UPlayerCursorManager* NewCursorManager)
	{
		CursorManager = NewCursorManager;
	}

	AActor* OwningActor;
	/** Offset from the player location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FVector GunOffset;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

protected:

	class UPlayerCursorManager* CursorManager;
};
