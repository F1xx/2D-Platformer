// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinPickup.h"
#include "Components/BoxComponent.h"
#include "PlayerPawn.h"
#include "MyGameStateBase.h"

ACoinPickup::ACoinPickup()
{
	Tags.Add("Coin Pickup");
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACoinPickup::OnOverlapBegin);
}

void ACoinPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACoinPickup::BeginPlay()
{
	Super::BeginPlay();
}

void ACoinPickup::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		APlayerPawn* playerPawn = Cast<APlayerPawn>(OtherActor);
		if (playerPawn)
		{
			playerPawn->GetGameState()->AddPlayerScore(ScoreValue);

			Destroy();
		}
	}
}
