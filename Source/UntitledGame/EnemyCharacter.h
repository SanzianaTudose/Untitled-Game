// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ElementInteractionManager.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class UNTITLEDGAME_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	void Attack(); // Functionality for a single attack. For now, fires a single shot.

	void HandleDeath();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EStatus Status;

	void UpdateStatus(EElement status);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStatusMaterial();
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	FVector ProjectileOffset = FVector(90.f, 0.f, 0.f);

	
};
