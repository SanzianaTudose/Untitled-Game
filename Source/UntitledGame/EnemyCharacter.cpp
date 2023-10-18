// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
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

	UE_LOG(LogTemp, Warning, TEXT("FireRotation: %s Location: %s"), *FireRotation.ToString(), *ProjectileSpawnLocation.ToString());

	AUntitledGameProjectile* Projectile = GetWorld()->SpawnActor<AUntitledGameProjectile>(ProjectileSpawnLocation, FireRotation);
	Projectile->SetOwner(this);
}

void AEnemyCharacter::HandleDeath()
{
	Destroy();
}

