// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponCore.h"
#include "PlayerCharacter.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(Player, Log, All);

UCLASS()
class UNTITLEDGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const
	{
		return TopDownCameraComponent;
	}
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const
	{
		return CameraBoom;
	}

	UPROPERTY(Category = General, EditAnywhere, BlueprintReadWrite)
	class UPlayerCursorManager* CursorManager;

	UPROPERTY(Category = WeaponSystem, EditAnywhere, BlueprintReadWrite)
	class UWeaponCore* WeaponCore;
	UPROPERTY(Category = WeaponSystem, EditAnywhere, BlueprintReadWrite)
	class UShootingController* ShootingController;

	void OnFire();
	UFUNCTION(BlueprintCallable)
	void PrintCoreStats();
	void HandleDeath();

protected:
	virtual void BeginPlay() override;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};
