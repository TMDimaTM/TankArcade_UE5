// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:

	void SetTurretRotation(FVector TargetLocation, float DeltaTime);
	void Fire();

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurretRotationSpeed = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectileActor> Projectile;
};
