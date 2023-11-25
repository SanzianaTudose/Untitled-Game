// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"

#include "EnemyCharacter.h"
#include "UntitledGameGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemySpawner::SpawnEnemy()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemySpawner: World could not be found"));
		return;
	}

	// Do not spawn any more Enemies if MaxEnemyCount has been reached 
	int32 EnemyCount;
	if (UntitledGameGameMode)
		EnemyCount = UntitledGameGameMode->GetEnemyCount();

	if (EnemyCount >= MaxEnemyCount) return;

	// Find a random location on the NavMesh
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(World);
	if (!NavSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemySpawner: NavigationSystemV1 could not be found"));
		return;
	}

	FNavLocation Result;
	FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(World, 0)->GetActorLocation();

	bool bFoundPath = NavSystem->GetRandomReachablePointInRadius(PlayerLocation, SpawnRadius, Result);
	if (!bFoundPath) // Only spawn Enemies when Player is in a reachable position
		return;

	FVector SpawnLocation = Result.Location;
	AActor* SpawnedEnemy = World->SpawnActor<AEnemyCharacter>(EnemyBP, SpawnLocation, FRotator::ZeroRotator);
	if (UntitledGameGameMode && SpawnedEnemy)
		UntitledGameGameMode->NotifyEnemySpawned();
}

void AEnemySpawner::StartSpawning()
{

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, SpawnRate, true);

	UntitledGameGameMode = Cast<AUntitledGameGameMode>(UGameplayStatics::GetGameMode(this));
	if (UntitledGameGameMode == nullptr)
		UE_LOG(LogTemp, Error, TEXT("EnemySpawner: GameMode not found."));
}

