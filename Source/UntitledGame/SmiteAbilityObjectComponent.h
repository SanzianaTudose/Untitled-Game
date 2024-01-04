// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityObjectComponent.h"
#include "SmiteAbilityObjectComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNTITLEDGAME_API USmiteAbilityObjectComponent : public UAbilityObjectComponent
{
	GENERATED_BODY()
	
	protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OnSmiteHit(AActor* OtherActor, FVector hitPoint);
	public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
