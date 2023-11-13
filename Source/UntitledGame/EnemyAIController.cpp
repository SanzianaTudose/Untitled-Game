// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr)
        UE_LOG(LogTemp, Error, TEXT("EnemyAIController: PlayerPawn not found."));
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