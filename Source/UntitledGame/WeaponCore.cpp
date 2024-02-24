#include "WeaponCore.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include <iostream>
#include <random>

// Constructor
UWeaponCore::UWeaponCore()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.
    PrimaryComponentTick.bCanEverTick = true;

    // Initialize default properties
    OwningActor = GetOwner();
    GunOffset = FVector(90.f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void UWeaponCore::BeginPlay()
{
    Super::BeginPlay();

    // Initialize abilities
    AbilityIndex = 0;
    AbilitiesClasses = TArray<TSubclassOf<AActor>>();
    AbilitiesClasses.Add(AUntitledGameProjectile::StaticClass());
    bCanFire = true;
}

// Generate weapon stats based on the provided level
void UWeaponCore::GenerateStats(int level)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // Default stats
    Stats[WeaponStat::MaxAbilities] = 1.0f;

    // Randomize fire rate
    std::uniform_real_distribution<> fireRateDist(0.25f, 0.75f);
    Stats[WeaponStat::FireRate] = fireRateDist(gen);

    // Randomize reload time
    std::uniform_real_distribution<> reloadTimeDist(0.5f, 1.0f);
    Stats[WeaponStat::ReloadTime] = reloadTimeDist(gen);
}

#pragma region Abilities

// Add a new ability to the weapon
void UWeaponCore::AddAbility(TSubclassOf<AActor> AbilityClass)
{
    AbilitiesClasses.Add(AbilityClass);

    // Ensure the abilities list does not exceed the maximum size
    if (AbilitiesClasses.Num() > Stats[WeaponStat::MaxAbilities])
    {
        AbilitiesClasses.RemoveAt(0, 1, true); // Remove the first ability
    }
}

// Placeholder for RemoveAbility method
void UWeaponCore::RemoveAbility(AUntitledGameProjectile* Ability)
{
    // TODO: Implement ability removal logic
}

// Activate the current ability
void UWeaponCore::ActivateAbility(FVector SpawnLocation, FRotator SpawnRotation)
{
    if (!bCanFire || AbilitiesClasses.Num() == 0) return;

    UWorld* World = GetWorld();
    if (!World) return; // Ensure the world is valid

    // Spawn the ability actor
    AActor* NewProjectile = World->SpawnActor<AActor>(AbilitiesClasses[AbilityIndex], SpawnLocation, SpawnRotation);
    NewProjectile->SetOwner(OwningActor);
    bCanFire = false;

    // Set up timers for firing and reloading
    FTimerHandle TimerHandle_ShotTimerExpired;
    float TimerDuration = (AbilityIndex == AbilitiesClasses.Num() - 1) ? Stats[WeaponStat::ReloadTime] : Stats[WeaponStat::FireRate];
    World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &UWeaponCore::ShotTimerExpired, TimerDuration);

    // Update the ability index
    AbilityIndex++;
    AbilityIndex %= AbilitiesClasses.Num();

    // Set up a timer to decrement the reload time
    CurrentReloadTimeLeft = Stats[WeaponStat::FireRate];
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReloadTimeDecrement, this, &UWeaponCore::DecrementReloadTime, 0.1f, true);
}

#pragma endregion Abilities

// Handle weapon fire action
void UWeaponCore::OnFire()
{
    // Get location of the owning actor
    FVector OwningActorLocation = OwningActor ? OwningActor->GetActorLocation() : FVector(0, 0, 0);

    // Check if it's okay to fire
    if (bCanFire)
    {
        // Determine fire direction based on cursor position
        auto CursorToWorld = CursorManager->GetCursorToWorld();
        if (!CursorToWorld) return;

        FVector CursorLocation = CursorToWorld->GetComponentLocation();
        CursorLocation.Z = OwningActorLocation.Z;
        FVector FireDirection = CursorLocation - OwningActorLocation;
        FRotator FireRotation = FireDirection.Rotation();

        // Calculate projectile spawn location
        const FVector ProjectileSpawnLocation = OwningActorLocation + FireRotation.RotateVector(GunOffset);

        // Activate the ability if the world is valid
        UWorld* const World = GetWorld();
        if (World != nullptr)
        {
            ActivateAbility(ProjectileSpawnLocation, FireRotation);
        }

        // Play fire sound if specified
        if (FireSound != nullptr)
        {
            // UGameplayStatics::PlaySoundAtLocation(this, FireSound, OwningActorLocation);
        }
    }
}

// Callback when shot timer expires
void UWeaponCore::ShotTimerExpired()
{
    bCanFire = true;
}

#pragma region Components

// Add a component to the weapon
void UWeaponCore::AddComponent(UComponent* Component)
{
    if (!Component) return;

    // Prevent adding the same component twice
    if (Components.Contains(Component))
    {
        UE_LOG(LogTemp, Warning, TEXT("WeaponCore: Component cannot be added twice!"));
        return;
    }

    // Apply component modifiers and add to the list
    ApplyComponentModifiers(Component, true);
    Components.Add(Component);
}

// Remove a component from the weapon
void UWeaponCore::RemoveComponent(UComponent* Component)
{
    if (!Component) return;

    // Ensure the component is in the list before removing
    if (!Components.Contains(Component))
    {
        UE_LOG(LogTemp, Warning, TEXT("WeaponCore: Cannot remove Component that has not been already added!"));
        return;
    }

    // Revert component modifiers and remove from the list
    ApplyComponentModifiers(Component, false);
    Components.Remove(Component);
}

// Apply or revert modifiers of a component
void UWeaponCore::ApplyComponentModifiers(UComponent* Component, bool isAdded)
{
    float Sign = isAdded ? 1 : -1;
    for (auto& Modifier : Component->Modifiers)
    {
        Stats.Emplace(Modifier.Key, Stats[Modifier.Key] + Sign * Modifier.Value);
    }
}

#pragma endregion Components

// Handle decrementing reload time
void UWeaponCore::DecrementReloadTime()
{
    CurrentReloadTimeLeft -= 0.1f; // Decrement by frame time

    // Stop updating if reload time has expired
    if (CurrentReloadTimeLeft <= 0.0f)
    {
        GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ReloadTimeDecrement);
        ShotTimerExpired();
    }
}
