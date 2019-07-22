// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletPickup.h"
#include "Components/BoxComponent.h"
#include "PlayerPawn.h"
#include "MyGameStateBase.h"

ABulletPickup::ABulletPickup() :Super()
{
    Tags.Add("Bullet Pickup");
	Box->OnComponentBeginOverlap.AddDynamic(this, &ABulletPickup::OnOverlapBegin);
}

void ABulletPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Floating part
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	//Scale our height by a factor of 20
	NewLocation.Z += DeltaHeight * 20.0f;
	RunningTime += DeltaTime * 8;
	SetActorLocation(NewLocation);
}

void ABulletPickup::BeginPlay()
{
    Super::BeginPlay();
}

void ABulletPickup::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (OtherActor)
    {
        APlayerPawn* playerPawn = Cast<APlayerPawn>(OtherActor);
		if (playerPawn)
		{
			playerPawn->SetBulletType(Bullet_Type);
			//add ammo to the player pawn
			playerPawn->GetGameState()->AddPlayerAmmo(AmmoAmount);
			
			Destroy();
		}
    }
}