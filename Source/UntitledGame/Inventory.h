// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

UENUM(BlueprintType)
enum class ItemType : uint8
{
    WeaponCore,
    ArmorCore,
    Ability,
	Stock,
	Barrel,
	Sight,
	Trigger,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNTITLEDGAME_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

public:
	UPROPERTY(Category = "Inventory", EditAnywhere, BlueprintReadWrite)
	TArray<UDataAsset*> Items;
	UPROPERTY(Category = "Inventory", EditAnywhere, BlueprintReadWrite)
	int MaxItems;
	UPROPERTY(Category = "Inventory", EditAnywhere, BlueprintReadWrite)
	int CurrentItems;
	UPROPERTY(Category = "Inventory", EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> InventoryWidget;
	UPROPERTY(Category = "Inventory", EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> ItemWidget;
	UPROPERTY(Category = "IconMapping", EditAnywhere, BlueprintReadOnly)
    TMap<ItemType, UTexture2D*> IconMap;

	UFUNCTION(BlueprintCallable)
	void AddItem( UDataAsset* Item);
	UFUNCTION(BlueprintCallable)
	void RemoveItem(int Slot);
	UFUNCTION(BlueprintCallable)
	void DisplayInventory();
	UFUNCTION(BlueprintCallable)
	UDataAsset* QueryItem(int Slot);

};
