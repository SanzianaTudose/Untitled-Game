// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Blueprint.h"
#include "WeaponCore.h"
#include "ItemSpawner.generated.h"

UENUM(BlueprintType)
enum class ItemType : uint8
{
    WeaponCore UMETA(DisplayName = "WeaponCore"),
    Ability UMETA(DisplayName = "Ability")
};

UCLASS()
class UNTITLEDGAME_API AItemSpawner : public AActor
{
    GENERATED_BODY()

public:	
    // Sets default values for this actor's properties
    AItemSpawner();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSystem")
    ItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSystem", meta = (EditCondition = "ItemType == ItemType::WeaponCore"))
    int MaxAbility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSystem", meta = (EditCondition = "ItemType == ItemType::WeaponCore"))
    float FireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSystem", meta = (EditCondition = "ItemType == ItemType::WeaponCore"))
    float ReloadTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSystem", meta = (EditCondition = "ItemType == ItemType::Ability"))
    TSubclassOf<AActor> AbilityType;

	UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<AActor> AbilityItemBlueprint;

    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<AActor> WeaponItemDebugBlueprint;

	UFUNCTION(BlueprintCallable)
	void RespawnItem();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
	void SpawnItem();

public:	

};