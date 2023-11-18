// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

// Keep tracks of Enemy count and regularly spawns Enemies in a random location
// up to a max number of enemies 

UCLASS()
class UNTITLEDGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;

	void SpawnEnemy();

	float SpawnRate = 5.f;
	FTimerHandle SpawnTimerHandle;
};
