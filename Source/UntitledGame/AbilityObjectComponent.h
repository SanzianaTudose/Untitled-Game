// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElementInteractionManager.h"
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
	UStaticMeshComponent* MainObj; // the main mesh representing the ability object
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	AElementInteractionManager* EIM;
	//the element type of this object
	UPROPERTY(EditAnywhere)
	EElement Element;
	//list of effects to apply to an enemy that this object hits
	//Effect[] 

	float Damage;
	//will determine if the ability object will be able to hit more than one enemy
	bool bDestroyOnHit = true;
	float Range;
	FVector InitialPosition;

	void SetData(/*Element, Effect[]*/ float d, bool doh, float r, AElementInteractionManager* e);

	UFUNCTION()
	void OnEnemyHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
