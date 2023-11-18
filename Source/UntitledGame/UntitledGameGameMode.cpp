// Copyright Epic Games, Inc. All Rights Reserved.

#include "UntitledGameGameMode.h"
#include "PlayerCharacter.h"
#include "PlayerCharacterController.h"
#include "UObject/ConstructorHelpers.h"
#include "EnemyCharacter.h"

AUntitledGameGameMode::AUntitledGameGameMode()
{
	// Use custom PlayerController class
	PlayerControllerClass = APlayerCharacterController::StaticClass();

	// Set default pawn class to custom Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
		DefaultPawnClass = PlayerPawnBPClass.Class;
}

void AUntitledGameGameMode::OnActorDeath(AActor* DeadActor)
{
	// if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(DeadActor))
		// PlayerCharacter->HandleDeath();

	if (AEnemyCharacter* KilledEnemy = Cast<AEnemyCharacter>(DeadActor))
	{
		KilledEnemy->HandleDeath();
		EnemyCount--;
	}
}

void AUntitledGameGameMode::NotifyEnemySpawned()
{
	EnemyCount++;
}

