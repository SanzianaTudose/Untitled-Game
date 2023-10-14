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

const FName APlayerCharacterController::MoveForwardBinding("MoveForward");
const FName APlayerCharacterController::MoveRightBinding("MoveRight");

void APlayerCharacterController::BeginPlay()
{
	PlayerPawn = GetPawn();
	if (PlayerPawn == nullptr)
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacterController: Player Pawn not found!"));

	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;

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

	SetControlRotation(NewRot);
}

void APlayerCharacterController::OnFire()
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		FVector FireDirection;
		// get mouse direction
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			FHitResult HitResult;
			ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Visibility);
			bool bHit = PlayerController->GetHitResultUnderCursorByChannel(TraceType, true, HitResult);

			if (bHit)
			{
				// Process the hit result, e.g.,:
				FVector HitLocation = HitResult.Location;
				HitLocation.Z = PlayerPawn->GetActorLocation().Z;
				FireDirection = HitLocation - PlayerPawn->GetActorLocation();
			}
		}
		const FRotator FireRotation = FireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector ProjectileSpawnLocation = PlayerPawn->GetActorLocation() + FireRotation.RotateVector(GunOffset);


		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// spawn the projectile
			auto Projectile = World->SpawnActor<AUntitledGameProjectile>(ProjectileSpawnLocation, FireRotation);
			Projectile->SetOwner(this);
		}

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &APlayerCharacterController::ShotTimerExpired, FireRate);

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, PlayerPawn->GetActorLocation());
		}

		bCanFire = false;
	}
}

void APlayerCharacterController::ShotTimerExpired()
{
	bCanFire = true;
}
