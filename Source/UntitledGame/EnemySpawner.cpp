// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"

#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, SpawnRate, true);
}

void AEnemySpawner::SpawnEnemy()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemySpawner: World could not be found"));
		return;
	}

	FVector SpawnLocation = UGameplayStatics::GetPlayerCharacter(World, 0)->GetActorLocation(); // TODO: Change location to random point on nav mesh
	World->SpawnActor<AEnemyCharacter>(EnemyBP, SpawnLocation, FRotator::ZeroRotator);

	UE_LOG(LogTemp, Error, TEXT("Enemy SPAWNED"));
}

