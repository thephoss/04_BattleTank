// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());

			//TODO tell tank to aim here
	}
	
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocationOUT) const
{
	HitLocationOUT = FVector(1.0);
	return true;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


