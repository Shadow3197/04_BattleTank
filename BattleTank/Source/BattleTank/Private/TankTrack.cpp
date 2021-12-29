// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

#include "SpawnPoint.h"
#include "SprungWheel.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DrivingTrack(CurrentThrottle);
}

void UTankTrack::DrivingTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel * Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child); 
		if (!SpawnPointChild) continue;
		AActor* SpawnChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnChild);
		if (!SprungWheel) continue;
		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}

