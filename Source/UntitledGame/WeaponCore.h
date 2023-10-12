#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UntitledGameProjectile.h"
#include "WeaponCore.generated.h"

UCLASS()
class UNTITLEDGAME_API AWeaponCore : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponCore();

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	int MaxAbilities;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	int AbilityIndex;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	float FireRate;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	float ReloadTime;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	bool bCanFire;

	void AWeaponCore::GenerateStats(int level);
	void AWeaponCore::AddAbility(AUntitledGameProjectile* Ability);
	void AWeaponCore::RemoveAbility(AUntitledGameProjectile* Ability);
	void AWeaponCore::ActivateAbitlity(FVector SpawnLocation, FRotator SpawnRotation);
	void AWeaponCore::ShotTimerExpired();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int PlayerLevel;
	TArray<TSubclassOf<AUntitledGameProjectile>> AbilitiesClasses;

};
