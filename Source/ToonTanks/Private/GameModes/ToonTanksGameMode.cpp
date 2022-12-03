// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/ToonTanksPlayerController.h"
#include "TimerManager.h"

AToonTanksGameMode::AToonTanksGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	StartTime = 3.0f;
	RemainingTime = StartTime;
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	PlayerController->SetPlayerInputEnabled(false);

	GetWorldTimerManager().SetTimer(StartTimerHandle, this, &AToonTanksGameMode::HandleGameStart, StartTime, false);
}

void AToonTanksGameMode::Tick(float DeltaTime)
{
	if (!bGameStarted)
	{
		RemainingTime = GetWorldTimerManager().GetTimerRemaining(StartTimerHandle);
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	PlayerController->SetPlayerInputEnabled(true);
	bGameStarted = true;
}