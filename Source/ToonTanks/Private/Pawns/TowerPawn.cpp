// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TowerPawn.h"

ATowerPawn::ATowerPawn()
{
	MaxViewDistance = 500.0f;
	FireRate = 3.0f;
}

void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FTimerHandle FireRateTimerHandle;
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATowerPawn::CheckFireCondition, FireRate, true);
}

void ATowerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanSeePlayer())
	{
		SetTurretRotation(PlayerPawn->GetActorLocation(), DeltaTime);
	}
}

float ATowerPawn::GetDistanceToPlayer()
{
	return FVector::Distance(GetActorLocation(), PlayerPawn->GetActorLocation());
}

bool ATowerPawn::CanSeePlayer()
{
	return GetDistanceToPlayer() <= MaxViewDistance;
}

void ATowerPawn::CheckFireCondition()
{
	if (CanSeePlayer())
	{
		Fire();
	}
}