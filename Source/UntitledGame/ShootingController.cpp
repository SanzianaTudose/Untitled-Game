// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingController.h"
#include "Components/InputComponent.h"
#include "Sound/SoundBase.h"
#include "WeaponCore.h"
#include "PlayerCursorManager.h"

UShootingController::UShootingController()
{
	PrimaryComponentTick.bCanEverTick = false;
	OwningActor = GetOwner();
	GunOffset = FVector(90.f, 0.f, 0.f);
}

void UShootingController::OnFire()
{
	UWeaponCore* WeaponCore = Cast<UWeaponCore>(OwningActor->GetComponentByClass(UWeaponCore::StaticClass()));
	FVector OwningActorLocation = FVector(0, 0, 0);
	if (OwningActor != nullptr)
		OwningActorLocation = OwningActor->GetActorLocation();

	// If it's ok to fire again
	if (WeaponCore != nullptr && WeaponCore->bCanFire)
	{
		FVector FireDirection;
		// get mouse direction
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			FHitResult HitResult;
			// ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Visibility);
			bool bHit = PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

			if (bHit)
			{
				// Process the hit result, e.g.,:
				FVector HitLocation = HitResult.Location;
				HitLocation.Z = OwningActorLocation.Z;
				FireDirection = HitLocation - OwningActorLocation;
			}
		}
		const FRotator FireRotation = FireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector ProjectileSpawnLocation = OwningActorLocation + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// spawn the projectile
			if (WeaponCore != nullptr)
			{
				WeaponCore->ActivateAbitlity(ProjectileSpawnLocation, FireRotation, OwningActor);
			}
		}

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
			//UGameplayStatics::PlaySoundAtLocation(this, FireSound, OwningActorLocation);
		}
	}
}
