// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UntitledGameGameMode.generated.h"

UCLASS(MinimalAPI)
class AUntitledGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUntitledGameGameMode();

	void OnActorDeath(AActor* DeadActor);

	// Called by EnemySpawner class when a new Enemy is spawned
	void NotifyEnemySpawned();

	FORCEINLINE int32 GetEnemyCount()
	{
		return EnemyCount;
	}

private:
	int32 EnemyCount = 0;
};



