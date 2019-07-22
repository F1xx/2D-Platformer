// Fill out your copyright notice in the Description page of Project Settings.

#include "AmmoPickup.h"
#include "Components/BoxComponent.h"
#include "PlayerPawn.h"
#include "MyGameStateBase.h"

AAmmoPickup::AAmmoPickup()
{
    Tags.Add("AmmoPickup");
    Box->OnComponentBeginOverlap.AddDynamic(this, &AAmmoPickup::OnOverlapBegin);
}

void AAmmoPickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAmmoPickup::BeginPlay()
{
    Super::BeginPlay();
}

void AAmmoPickup::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (OtherActor)
    {
        APlayerPawn* playerPawn = Cast<APlayerPawn>(OtherActor);
        if (playerPawn)
        {
            playerPawn->GetGameState()->AddPlayerAmmo(AmmoValue);

            Destroy();
        }
    }
}
