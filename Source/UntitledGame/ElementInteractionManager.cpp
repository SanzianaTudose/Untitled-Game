// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementInteractionManager.h"

// Sets default values
AElementInteractionManager::AElementInteractionManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElementInteractionManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElementInteractionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AElementInteractionManager::AbilityEnemyInteract(EElement ability, EStatus enemy, FVector location, AActor* other)
{
	UE_LOG(LogTemp, Display, TEXT("Did element interaction %i"), enemy);

	if((ability == EElement::Fire && enemy == EStatus::SlimeCovered)
	|| (ability == EElement::Slime && enemy == EStatus::OnFire))
	{
		UE_LOG(LogTemp, Display, TEXT("KABOOM"));
		//AActor* actor = other->GetWorld()->SpawnActor<AActor>(SlimeExplosion, location, other->GetActorRotation());
		
	}
}

