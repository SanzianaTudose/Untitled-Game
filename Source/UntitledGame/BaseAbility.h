// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAbility.generated.h"

UCLASS()
class UNTITLEDGAME_API ABaseAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void spawnObjects();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//the element type of this object
	//Element
	//list of effects to apply to an enemy that this object hits
	//Effect[] 
	UPROPERTY(EditAnywhere)
	float damage = 10;
	//will determine if the ability object will be able to hit more than one enemy
	UPROPERTY(EditAnywhere)
	bool destroyOnHit = true;
	UPROPERTY(EditAnywhere)
	float range = 10;
	UPROPERTY(EditAnywhere)
	FVector initialPosition;


	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AActor>> abilityObjects;

};
