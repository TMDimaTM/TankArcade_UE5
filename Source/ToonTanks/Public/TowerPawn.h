// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TowerPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATowerPawn : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATowerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Vision")
	float MaxViewDistance;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireRate;

	APawn* PlayerPawn;

	float GetDistanceToPlayer();
	bool CanSeePlayer();

	void CheckFireCondition();

};