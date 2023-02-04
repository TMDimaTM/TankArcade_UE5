// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/ProjectileActor.h"
#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

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

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ABasePawn::SetTurretRotation(const FVector& TargetLocation, float DeltaTime)
{
	FRotator CurrentRotation = TurretMesh->GetComponentRotation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetComponentLocation(), TargetLocation);

	CurrentRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, TurretRotationSpeed);
	TurretMesh->SetWorldRotation(FRotator(0.0f, CurrentRotation.Yaw, 0.0f));
}

void ABasePawn::Fire()
{
	if (Projectile)
	{
		AProjectileActor* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileActor>(Projectile, ProjectileSpawnPoint->GetComponentTransform());
		SpawnedProjectile->SetOwner(this);
	}
}

void ABasePawn::ParentHandleDestruction() const
{
	if (DeathEffect != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathEffect, GetActorTransform());
	}
	if (DeathSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
}