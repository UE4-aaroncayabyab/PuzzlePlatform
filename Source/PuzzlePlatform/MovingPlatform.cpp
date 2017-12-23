// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector Location = GetActorLocation();
	if (HasAuthority())
	{		
		Location += FVector(speed * DeltaSeconds, 0.f, 0.f);
		SetActorLocation(Location);
	}
	else
	{
		Location += FVector(-speed * DeltaSeconds, 0.f, 0.f);
		SetActorLocation(Location);
	}
	
}
