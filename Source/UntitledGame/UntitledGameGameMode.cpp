// Copyright Epic Games, Inc. All Rights Reserved.

#include "UntitledGameGameMode.h"
#include "UntitledGamePawn.h"

AUntitledGameGameMode::AUntitledGameGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AUntitledGamePawn::StaticClass();
}

