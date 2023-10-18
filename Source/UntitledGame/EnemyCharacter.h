// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class UNTITLEDGAME_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	void Attack(); // Functionality for a single attack. For now, fires a single shot.
	void HandleDeath();

protected:
	virtual void BeginPlay() override;

private:
	USceneComponent* ProjectileSpawnPoint;
};
