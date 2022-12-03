// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/ToonTanksPlayerController.h"



void AToonTanksPlayerController::SetPlayerInputEnabled(bool bEnabled)
{
	if (bEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bEnabled;
	GetPawn()->SetActorTickEnabled(bEnabled);
}