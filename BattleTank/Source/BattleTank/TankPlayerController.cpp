// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));

	ATank* Tank = GetControlledTank();

	if (!Tank)
	{
		UE_LOG(LogTemp, Error, TEXT("No Pawn Possession Found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank is: %s"), *Tank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
	
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()){return;}

	FVector HitLocation; //OUT
	if (GetSightRayHitLocation(HitLocation)) //is going to lione trace
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocationOUT) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(CrosshairX*ViewportSizeX, CrosshairY*ViewportSizeY);
	
	//de-project the screen position of the crosshair to a world direction
	FVector LookDirection; //OUT
	
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//line trace along that direction(look direction), see what we hit
		
		GetLookVectorHitLocation(LookDirection, HitLocationOUT);
	}
	
	
	return true;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocationOUT) const
{
	FHitResult HitResult;
	auto LineStart = PlayerCameraManager->GetCameraLocation();
	auto LineEnd = LineStart + (LookDirection* LineTraceRange);
	
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		LineStart,
		LineEnd,
		ECollisionChannel::ECC_Visibility)
	)
	{
		HitLocationOUT = HitResult.Location;
		return true;
	}
	HitLocationOUT = FVector(0);
	
	return false;
}

