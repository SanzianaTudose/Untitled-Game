// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilityObjectSpawner.generated.h"

UCLASS()
class UNTITLEDGAME_API AAbilityObjectSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilityObjectSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnObjects();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//the element type of this object
	//Element
	//list of effects to apply to an enemy that this object hits
	//Effect[] 
	UPROPERTY(EditAnywhere)
	float Damage = 50;
	//will determine if the ability object will be able to hit more than one enemy
	UPROPERTY(EditAnywhere)
	bool bDestroyOnHit = true;
	UPROPERTY(EditAnywhere)
	float Range = 10;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AActor>> AbilityObjects;

};
