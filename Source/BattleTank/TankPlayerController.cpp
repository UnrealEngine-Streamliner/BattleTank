// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Not Possesing a Tank"));
	} 
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Possesing: %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float deltaSeconds)
{
    Super::Tick(deltaSeconds);
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }
    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation))
    {
        
    }
    UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
    OutHitLocation = FVector(1.0);
    return true;
}
