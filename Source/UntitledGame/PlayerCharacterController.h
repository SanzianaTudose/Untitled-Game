// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

// Handles PlayerCharacter movement
UCLASS()
class UNTITLEDGAME_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float PlayerLevel;

	void OnFire();

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	void MovePlayer(float DeltaTime);
	void RotateToCursor();

private:
	virtual void BeginPlay() override;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	APawn* PlayerPawn;
};
