// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePickup.h"
#include "Components/BoxComponent.h"

ABasePickup::ABasePickup()
{
    Box->SetEnableGravity(false);
    
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Overlap); //player
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECR_Ignore); //enemy
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECR_Ignore); //Projectile

    Tags.Add("Pickup");
}

void ABasePickup::BeginPlay()
{
    Super::BeginPlay();
}

void ABasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}