// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNTITLEDGAME_API Inventory
{
public:
	Inventory();
	~Inventory();

	UPROPERTY(Category = Inventory, EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Items;
	UPROPERTY(Category = Inventory, EditAnywhere, BlueprintReadWrite)
	int MaxItems;
	UPROPERTY(Category = Inventory, EditAnywhere, BlueprintReadWrite)
	int CurrentItems;


	UFUNCTION(BlueprintCallable)
	void AddItem(int Slot, AActor* Item);
	UFUNCTION(BlueprintCallable)
	void RemoveItem(int Slot);
	UFUNCTION(BlueprintCallable)
	AActor* QueryItem(int Slot);

};
