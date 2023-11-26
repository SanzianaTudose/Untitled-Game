// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCursorManager.generated.h"


/*
   Holds information about the cursor location
   Shows cursor decal if enabled

   Attached to the Player Blueprint
*/

// TODO: Add option to toggle visibility of decal

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNTITLEDGAME_API UPlayerCursorManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerCursorManager();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE class UDecalComponent* GetCursorToWorld()
	{
		return CursorToWorld;
	}

protected:
	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	void MoveCursor();
};
