// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNTITLEDGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region SettersGetters
	
	void SetMaxHealth(float NewMaxHealth)
	{
		MaxHealth = NewMaxHealth;
	}

	// Used to also initialize current health value {Health}
	void SetMaxHealth(float NewMaxHealth, bool IsInitialArmorCore)
	{
		MaxHealth = NewMaxHealth;
		if (IsInitialArmorCore)
			Health = MaxHealth;
	}

#pragma endregion SettersGetters

protected:
	virtual void BeginPlay() override;

private:
	class AUntitledGameGameMode* UntitledGameGameMode;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 200.f;
	float Health = 0.f; // Holds current Health value

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);
};
