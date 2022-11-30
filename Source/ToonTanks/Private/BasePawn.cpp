// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectileActor.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	SetRootComponent(CapsuleComponent);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::SetTurretRotation(FVector TargetLocation, float DeltaTime)
{
	FRotator CurrentRotation = TurretMesh->GetComponentRotation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetComponentLocation(), TargetLocation);

	CurrentRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, TurretRotationSpeed);
	TurretMesh->SetWorldRotation(FRotator(0.0f, CurrentRotation.Yaw, 0.0f));
}

void ABasePawn::Fire()
{
	GetWorld()->SpawnActor<AProjectileActor>(Projectile, ProjectileSpawnPoint->GetComponentTransform());
}