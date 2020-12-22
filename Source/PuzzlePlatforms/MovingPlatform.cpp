// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() 
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	StartLocation = GetActorLocation();
	CurrentLocation = StartLocation;
	TargetLocation = GetActorLocation() + TargetLocationOffset;
	//UE_LOG(LogTemp, Error, TEXT("%s"), *CurrentLocation.ToString());

}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority() && (ActiveTriggers > 0))
	{
		CurrentLocation = GetActorLocation();
		float DistanceToMove = (TargetLocation - StartLocation).Size();
		float DistanceMoved = (CurrentLocation - StartLocation).Size();

		if (DistanceMoved >= DistanceToMove) {
			FVector Swap = StartLocation;
			StartLocation = TargetLocation;
			TargetLocation = Swap;
		}

		FVector Direction = (TargetLocation - StartLocation).GetSafeNormal();
		CurrentLocation += Direction * CmPerSecond * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers>0) ActiveTriggers--;
}