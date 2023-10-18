// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    OwnPawn = GetPawn();
    if (OwnPawn == nullptr)
        UE_LOG(LogTemp, Error, TEXT("EnemyAIController: Own Enemy Pawn not found!"));

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr)
        UE_LOG(LogTemp, Error, TEXT("EnemyAIController: PlayerPawn not found."));

    // Regularly call AttackAttempt(). Might not be the most efficient way to do it, change later if needed.
    GetWorldTimerManager().SetTimer(AttackRateTimerHandle, this, &AEnemyAIController::AttackAttempt, AttackRate, true);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Only follow Player if they can be seen by Enemy
    if (LineOfSightTo(PlayerPawn))
    {
        SetFocus(PlayerPawn);
        MoveToActor(PlayerPawn, AcceptanceRadius);
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }
}

void AEnemyAIController::Attack()
{
    // TODO: Implement this so it shoots a projectile waiting some time in between shots
    UE_LOG(LogTemp, Warning, TEXT("ATTACK"));
}

void AEnemyAIController::AttackAttempt()
{
    if (PlayerPawn == nullptr) return;

    float Distance = FVector::Dist(OwnPawn->GetActorLocation(), PlayerPawn->GetActorLocation());
    if (LineOfSightTo(PlayerPawn) && Distance <= AttackRange)
        Attack();
}