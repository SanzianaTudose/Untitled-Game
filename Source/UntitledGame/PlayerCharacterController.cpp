// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "Components/InputComponent.h"

const FName APlayerCharacterController::MoveForwardBinding("MoveForward");
const FName APlayerCharacterController::MoveRightBinding("MoveRight");

void APlayerCharacterController::BeginPlay()
{
    PlayerPawn = GetPawn();
    if (PlayerPawn == nullptr)
        UE_LOG(LogTemp, Error, TEXT("PlayerCharacterController: Player Pawn not found!"));

}

void APlayerCharacterController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    MovePlayer(DeltaTime);
}

void APlayerCharacterController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Set up gameplay key bindings
    InputComponent->BindAxis(MoveForwardBinding);
    InputComponent->BindAxis(MoveRightBinding);
}

void APlayerCharacterController::MovePlayer(float DeltaTime)
{
    // Find movement direction
    const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
    const float RightValue = GetInputAxisValue(MoveRightBinding);

    // Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
    const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

    PlayerPawn->AddMovementInput(MoveDirection);
}
