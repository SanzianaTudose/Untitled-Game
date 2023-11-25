// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "UntitledGameProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "PlayerCharacter.h"

const FName APlayerCharacterController::MoveForwardBinding("MoveForward");
const FName APlayerCharacterController::MoveRightBinding("MoveRight");

void APlayerCharacterController::BeginPlay()
{
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
    PlayerPawn = GetPawn();
    if (PlayerPawn == nullptr)
        UE_LOG(LogTemp, Error, TEXT("PlayerCharacterController: Player Pawn not found!"));

    PlayerLevel = 1;
}

void APlayerCharacterController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    MovePlayer(DeltaTime);
    RotateToCursor();
}

void APlayerCharacterController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Set up gameplay key bindings
    InputComponent->BindAxis(MoveForwardBinding);
    InputComponent->BindAxis(MoveRightBinding);
    InputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacterController::OnFire);
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

void APlayerCharacterController::RotateToCursor()
{
    FVector CurLocation = PlayerPawn->GetActorLocation();

    // Get cursor location
    FHitResult HitResult;
    GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
    FVector CursorLocation = HitResult.Location;

    FRotator CurRot = PlayerPawn->GetActorRotation();

    // Determine new rotator Yaw based on difference
    float NewYaw = (CursorLocation - CurLocation).Rotation().Yaw;;
    FRotator NewRot = FRotator(CurRot.Pitch, NewYaw, CurRot.Roll);

    PlayerPawn->SetActorRotation(NewRot);
}

void APlayerCharacterController::OnFire()
{
    APawn* MyPawn = GetPawn();
    if (MyPawn)
    {
        // Cast to your custom Pawn or Character class
        APlayerCharacter* PlayerScript = Cast<APlayerCharacter>(MyPawn);
        if (PlayerScript)
        {
            // Call a function on your character
            PlayerScript->OnFire();
        }
    }
}
