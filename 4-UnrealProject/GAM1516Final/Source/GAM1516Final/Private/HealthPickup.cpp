// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPickup.h"
#include "BaseActor.h"
#include "Components/BoxComponent.h"
#include "PlayerPawn.h"
#include "HealthComponent.h"

AHealthPickup::AHealthPickup() :Super()
{
    Box->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::OnOverlapBegin);
    Tags.Add("Health Pickup");
}

void AHealthPickup::BeginPlay()
{
    Super::BeginPlay();
}

void AHealthPickup::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (OtherActor)
    {
        APlayerPawn* playerPawn = Cast<APlayerPawn>(OtherActor);
        if (playerPawn)
        {
            if (playerPawn->GetCurrentHealth() < playerPawn->GetMaxHealth())
            {
                playerPawn->HealthComponent->TakeDamage(-10.0f);
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "This pick up Overlapped with - " + playerPawn->GetName());

				//its been picked up so destroy itself
                Destroy();
            }
        }
    }
}

void AHealthPickup::Tick(float DeltaTime)
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
