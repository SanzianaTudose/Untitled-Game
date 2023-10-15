// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityObjectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNTITLEDGAME_API UAbilityObjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityObjectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UStaticMeshComponent* mainObj; // the main mesh representing the ability object
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//the element type of this object
	//Element
	//list of effects to apply to an enemy that this object hits
	//Effect[] 

	float damage = 10;
	//will determine if the ability object will be able to hit more than one enemy
	bool destroyOnHit = true;
	float range = 10;
	FVector initialPosition;

	void setData(/*Element, Effect[]*/ float d, bool doh, float r);

	UFUNCTION()
	void OnEnemyHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
