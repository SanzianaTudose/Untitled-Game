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
};



