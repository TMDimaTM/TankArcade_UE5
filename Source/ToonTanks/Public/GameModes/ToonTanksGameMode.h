// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AToonTanksGameMode();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void CheckGameCondition(AActor* DeadActor) const;

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWin) const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Start")
	float StartTime;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Start")
	float RemainingTime;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Start")
	bool bGameStarted;

	UPROPERTY()
	class AToonTanksPlayerController* PlayerController;

	FTimerHandle StartTimerHandle;

	void HandleGameStart();
};
