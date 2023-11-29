// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "EnemyCharacter.h"
//#include "AbilityObjectComponent.h"
#include "ElementInteractionManager.generated.h"

UENUM()
enum class EElement : uint8 {
	None = 0,
	Fire = 1,
	Slime = 2
};

UENUM()
enum class EStatus : uint8 
{
	None = 0,
	OnFire = 1,
	SlimeCovered = 2
};

UCLASS()
class UNTITLEDGAME_API AElementInteractionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElementInteractionManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	static void AbilityEnemyInteract(EElement ability, EStatus enemy, FVector locationv, AActor* other);
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset References")
	//static TSubclassOf<AActor> SlimeExplosion;
	
	
};
