// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbility.h"
#include "AbilityObjectComponent.h"
// Sets default values
ABaseAbility::ABaseAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseAbility::BeginPlay()
{
	Super::BeginPlay();
	spawnObjects();
	
}

// Called every frame
void ABaseAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseAbility::spawnObjects()
{
	UWorld* const World = GetWorld();

	for(auto abilityClass : abilityObjects)
	{
		if (World != nullptr)
		{
			// spawn the projectile
			//this does not work
			/* AActor* actor = World->SpawnActor<abilityClass>(GetActorLocation(), GetActorRotation()); */
			//this works
			AActor* actor = World->SpawnActor(abilityClass);
			actor->SetActorRotation(GetActorRotation());
			actor->SetActorLocation(GetActorLocation());
			UAbilityObjectComponent* obj = actor->FindComponentByClass<UAbilityObjectComponent>();
			if(obj)
			{
				obj->setData(damage, destroyOnHit, range);
			}
			UE_LOG(LogTemp, Warning, TEXT("Object Spawned"));
		}
	}
}



