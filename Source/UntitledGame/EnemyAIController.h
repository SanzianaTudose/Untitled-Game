// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

// Handles Enemy movement and attack behaviors
// For now, all Enemies have the same attributes and behavior
UCLASS()
class UNTITLEDGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	void Attack(); // C
	void AttackAttempt(); // Called regularly based on {AttackRate} 

	APawn* OwnPawn;
	APawn* PlayerPawn;
	class AEnemyCharacter* OwnEnemy;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float AcceptanceRadius = 200.f; // How close the Enemy gets to Player

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackRange = 400.f;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackRate = 2.f;
	FTimerHandle AttackRateTimerHandle;
};
