// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MoveSpeed = 1000.0f;
	Damage = 25.0f;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComp->InitialSpeed = MoveSpeed;
	ProjectileMovementComp->MaxSpeed = MoveSpeed;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail"));
	TrailEffect->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);

	if (LaunchSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

void AProjectileActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr && OtherActor != GetOwner() && OtherActor != this)
	{
		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, GetInstigatorController(), this);
	}

	if (HitEffect != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorTransform());
	}
	if (HitSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
	if (CameraShake)
	{
		UGameplayStatics::PlayWorldCameraShake(this, CameraShake, GetActorLocation(), 0.0f, 5000.0f);
	}

	Destroy();
}