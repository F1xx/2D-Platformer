// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "BasePawn.h"
#include "MyGameStateBase.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
    currentHealth = 100.0f;
    maxHealth = 100.0f;
	
    //GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UHealthComponent::TakeDamage(float adamage)
{
    // if adamage is minus, it's increasing the health
	currentHealth -= adamage;

	if (currentHealth <= 0)
	{
		ABasePawn* pawn = Cast<ABasePawn>(GetOwner());
		if (pawn)
		{
			if (pawn->ActorHasTag("Enemy"))
			{
				pawn->GetGameState()->AddPlayerScore(10);
			}

			pawn->Die();
		}
		else
			GetOwner()->Destroy();
	}

	return adamage;
}
