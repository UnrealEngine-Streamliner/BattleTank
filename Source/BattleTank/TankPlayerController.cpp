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
    //UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const 
{
    // Find the crosshair position in pixel coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString());
    // De-project the screen position of the crosshair to a world direction
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
    }
    
    // Line-trace along that LookDirection, and see what we hit (up to max range)
    
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // To be discarded
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X, 
        ScreenLocation.Y, 
        CameraWorldLocation, 
        LookDirection
    );
}