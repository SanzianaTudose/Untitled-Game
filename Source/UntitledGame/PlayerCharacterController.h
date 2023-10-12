// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WeaponCore.h"
#include "PlayerCharacterController.generated.h"

// Handles PlayerCharacter movement
UCLASS()
class UNTITLEDGAME_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:

	/** Offset from the player location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	FVector GunOffset;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float PlayerLevel;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	AWeaponCore* WeaponCore;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	void MovePlayer(float DeltaTime);
	void OnFire();
	void ShotTimerExpired();

private:
	virtual void BeginPlay() override;

	/* Flag to control firing  */
	uint32 bCanFire : 1;
	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	APawn* PlayerPawn;
};
