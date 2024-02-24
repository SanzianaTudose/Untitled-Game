// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component.h"
#include "Blueprint/UserWidget.h"
#include "AbstractItem.h"	
#include "Inventory.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNTITLEDGAME_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<UAbstractItem*> Items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int MaxItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int CurrentItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TSubclassOf<UUserWidget> InventoryWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TSubclassOf<UUserWidget> ItemWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconMapping")
    TMap<TypeOfItem, UTexture2D*> IconMap;

	UFUNCTION(BlueprintCallable)
	void AddItem( UAbstractItem* Item);
	UFUNCTION(BlueprintCallable)
	void RemoveItem(int Slot);
	UFUNCTION(BlueprintCallable)
	void DisplayInventory();
	UFUNCTION(BlueprintCallable)
	UAbstractItem* QueryItem(int Slot);

};
