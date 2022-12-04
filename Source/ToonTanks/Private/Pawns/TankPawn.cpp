// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TankPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/ToonTanksPlayerController.h"
#include "GameModes/ToonTanksGameMode.h"



ATankPawn::ATankPawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	MoveSpeed = 100.0f;
	RotationSpeed = 90.0f;
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AToonTanksPlayerController>(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	SetTurretRotation(Hit.ImpactPoint, DeltaTime);
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATankPawn::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &ATankPawn::TurnAround);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATankPawn::Fire);
}

void ATankPawn::MoveForward(float Value)
{
	AddActorWorldOffset(GetActorForwardVector() * Value * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), true);
}

void ATankPawn::TurnAround(float Value)
{
	FRotator Rotation;
	Rotation.Yaw = Value * RotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(Rotation, true);
}

void ATankPawn::HandleDestruction_Implementation()
{
	ParentHandleDestruction();

	PlayerController->SetPlayerInputEnabled(false);
	SetActorHiddenInGame(true);

	bIsDead = true;
}