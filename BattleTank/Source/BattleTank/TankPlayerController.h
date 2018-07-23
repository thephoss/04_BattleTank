// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank * GetControlledTank() const;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AimTowardCrosshair();

private:
	bool GetSightRayHitLocation(FVector &HitLocationOUT) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocationOUT) const;

	UPROPERTY(EditAnywhere)
	float CrosshairX = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrosshairY = 0.33333f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0f;
};
