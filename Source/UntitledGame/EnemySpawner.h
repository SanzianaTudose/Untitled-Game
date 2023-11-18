// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

// Regularly spawns Enemies in a random location up to a max number of enemies 
// Notifies GameMode when a new Enemy is spawned 

UCLASS()
class UNTITLEDGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;

	void SpawnEnemy();

	UPROPERTY(EditAnywhere, Category = "Spawn");
	int32 MaxEnemyCount = 5;

	UPROPERTY(EditAnywhere, Category = "Spawn");
	float SpawnRate = 5.f;
	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Spawn");
	float SpawnRadius = 1000.f; // Radius to spawn (around the Player) 

	UPROPERTY(EditAnywhere, Category = "Spawn");
	TSubclassOf<class AEnemyCharacter> EnemyBP;

	class AUntitledGameGameMode* UntitledGameGameMode;
};
