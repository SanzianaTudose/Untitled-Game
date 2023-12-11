// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "ElementInteractionManager.h"
#include "Components/CapsuleComponent.h"
#include "UntitledGameProjectile.h"

AEnemyCharacter::AEnemyCharacter()
{
	// Set size for enemy capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::Attack()
{
	FRotator FireRotation = GetActorRotation();
	FVector ProjectileSpawnLocation = GetActorLocation() + FireRotation.RotateVector(ProjectileOffset);

	AUntitledGameProjectile* Projectile = GetWorld()->SpawnActor<AUntitledGameProjectile>(ProjectileSpawnLocation, FireRotation);
	Projectile->SetOwner(this);
}

void AEnemyCharacter::HandleDeath()
{
	Destroy();
}

void AEnemyCharacter::UpdateStatus(EElement otherElement)
{
	switch(otherElement)
	{
		case EElement::Fire:
			Status = EStatus::OnFire;
			break;
		case EElement::Slime:
			Status = EStatus::SlimeCovered;
			break;
		default:
			Status = EStatus::None;
			break;
	}

	AEnemyCharacter::UpdateStatusMaterial();
}

