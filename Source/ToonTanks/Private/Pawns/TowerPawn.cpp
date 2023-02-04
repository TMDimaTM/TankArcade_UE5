// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TowerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/ToonTanksGameMode.h"
#include "Pawns/TankPawn.h"

ATowerPawn::ATowerPawn()
{
	MaxViewDistance = 500.0f;
	FireRate = 3.0f;
}

void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	FTimerHandle FireRateTimerHandle;
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATowerPawn::CheckFireCondition, FireRate, true);
}

void ATowerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerPawn != nullptr && CanSeePlayer())
	{
		SetTurretRotation(PlayerPawn->GetActorLocation(), DeltaTime);
	}
}

float ATowerPawn::GetDistanceToPlayer() const
{
	return FVector::Distance(GetActorLocation(), PlayerPawn->GetActorLocation());
}

bool ATowerPawn::CanSeePlayer() const
{
	return GetDistanceToPlayer() <= MaxViewDistance;
}

void ATowerPawn::CheckFireCondition()
{
	if (CanSeePlayer() && !PlayerPawn->bIsDead)
	{
		Fire();
	}
}

void ATowerPawn::HandleDestruction_Implementation()
{
	ParentHandleDestruction();

	Destroy();
}