// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityObjectSpawner.h"
#include "AbilityObjectComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AAbilityObjectSpawner::AAbilityObjectSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbilityObjectSpawner::BeginPlay()
{
	Super::BeginPlay();
	FindInteractionManager();
	SpawnObjects();
	//Destroy();
}

// Called every frame
void AAbilityObjectSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAbilityObjectSpawner::FindInteractionManager()
{
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AElementInteractionManager::StaticClass());
	EIM = Cast<AElementInteractionManager>(FoundActor);

	if(!EIM)
	{
		UE_LOG(LogTemp, Error, TEXT("Element Interaction Manager not found"));
	}
} 

void AAbilityObjectSpawner::SpawnObjects()
{
	UWorld* const World = GetWorld();

	for(auto AbilityClass : AbilityObjects)
	{
		if (World != nullptr)
		{
			// spawn the projectile
			AActor* actor = World->SpawnActor<AActor>(AbilityClass, GetActorLocation(), GetActorRotation());
			UAbilityObjectComponent* obj = actor->FindComponentByClass<UAbilityObjectComponent>();
			if(obj)
			{
				//give it the needed stats
				obj->SetData(Damage, bDestroyOnHit, Range, EIM);
			}
		}
	}
}



