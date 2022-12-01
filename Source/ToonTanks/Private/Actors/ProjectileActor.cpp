// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &AProjectileActor::OnHit);
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr && OtherActor != GetOwner() && OtherActor != this)
	{
		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, GetInstigatorController(), this);
	}

	Destroy();
}