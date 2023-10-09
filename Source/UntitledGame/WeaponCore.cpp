// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponCore.h"
#include "playerCharacterController.h"
#include <iostream>
#include <random>

// Sets default values
AWeaponCore::AWeaponCore()
{

}

// Called when the game starts or when spawned
void AWeaponCore::BeginPlay()
{
	Super::BeginPlay();
	APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	PlayerLevel =  PlayerController->PlayerLevel;
}

void GenerateStats()
{
	int MaxAbilities = 1;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(1.0, 2.0);
	float FireRate = dis(gen);
	std::uniform_real_distribution<> dis2(1.0, 3.0);
	float ReloadTime = dis2(gen);
}

void AddAbility( )
{

}

void RemoveAbility()
{

}


