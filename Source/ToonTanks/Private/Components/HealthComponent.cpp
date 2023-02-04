// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/HandleDestructionInterface.h"
#include "GameModes/ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &ThisClass::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamagedActor != nullptr)
	{
		if (CurrentHealth > 0)
		{
			CurrentHealth -= Damage;
			if (CurrentHealth <= 0)
			{
				if (IHandleDestructionInterface* Interface = Cast<IHandleDestructionInterface>(DamagedActor))
				{
					Interface->Execute_HandleDestruction(DamagedActor);

					AToonTanksGameMode* GameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
					if (GameMode != nullptr)
					{
						GameMode->CheckGameCondition(DamagedActor);
					}
				}
			}
		}
	}
}

