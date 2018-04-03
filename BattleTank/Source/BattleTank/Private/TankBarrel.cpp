// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed , -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation =FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);
	if (MinElevation < 0) {
		UE_LOG(LogTemp, Warning, TEXT("%f: MinElevation below elevation"), MinElevation);
	}
	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
	
}

