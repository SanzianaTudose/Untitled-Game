// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCursorManager.h"

UPlayerCursorManager::UPlayerCursorManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCursorManager::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerCursorManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

