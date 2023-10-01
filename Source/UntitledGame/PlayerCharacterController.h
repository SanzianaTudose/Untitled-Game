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

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	// TODO: Add input and movement functionality
	
};
