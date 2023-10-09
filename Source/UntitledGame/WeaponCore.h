// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UntitledGameProjectile.h"
#include "playerCharacterController.h"
#include "WeaponCore.generated.h"

UCLASS()
class UNTITLEDGAME_API AWeaponCore : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponCore();

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	int MaxAbilities;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	float FireRate;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	float ReloadTime;

	void GenerateStats();
	void AddAbility(AUntitledGameProjectile* Ability);
	void RemoveAbility(AUntitledGameProjectile* Ability);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int PlayerLevel;
	TArray<AUntitledGameProjectile*> Abilities;

};
