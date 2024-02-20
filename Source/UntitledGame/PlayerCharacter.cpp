// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "WeaponCore.h"
#include "ShootingController.h"
#include "Inventory.h"
#include "PlayerCursorManager.h"

DEFINE_LOG_CATEGORY(Player);

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Don't rotate character to moving direction
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PrimaryActorTick.bCanEverTick = false;

	CursorManager = CreateDefaultSubobject<UPlayerCursorManager>(TEXT("CursorManager"));

	ShootingController = CreateDefaultSubobject<UShootingController>(TEXT("ShootingController"));
	ShootingController->OwningActor = this;
	ShootingController->SetCursorManager(CursorManager);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	WeaponCore = Cast<UWeaponCore>(GetComponentByClass(UWeaponCore::StaticClass()));
	WeaponCore->GenerateStats(1);
	PrintCoreStats();

	Inventory = Cast<UInventory>(GetComponentByClass(UInventory::StaticClass()));
	Inventory->DisplayInventory();
}

void APlayerCharacter::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player death!"));
}

void APlayerCharacter::OnFire()
{
	ShootingController->OnFire();
}

void APlayerCharacter::PrintCoreStats()
{
	UE_LOG(Player, Warning, TEXT("MaxAbilities: %f\n"), WeaponCore->Stats[WeaponStat::MaxAbilities]);
	UE_LOG(Player, Warning, TEXT("FireRate: %f\n"), WeaponCore->Stats[WeaponStat::FireRate]);
	UE_LOG(Player, Warning, TEXT("ReloadTime: %f\n"), WeaponCore->Stats[WeaponStat::ReloadTime]);
}


