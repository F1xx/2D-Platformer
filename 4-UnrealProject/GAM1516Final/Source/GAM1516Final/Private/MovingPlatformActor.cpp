// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatformActor.h"
#include "MovementFunctionLibrary.h"
#include "Components/BoxComponent.h"

AMovingPlatformActor::AMovingPlatformActor() : Super()
{
	Box->SetEnableGravity(false);
	Box->SetSimulatePhysics(false);

	Box->SetCollisionObjectType(ECC_WorldDynamic);
	Box->SetCollisionResponseToAllChannels(ECR_Ignore);

	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Block); //player
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECR_Block); //enemy
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECR_Block); //Projectile

	Tags.Add("Platform");
}

void AMovingPlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsMovingRight)
	{
		//Floating part
		FVector NewLocation = GetActorLocation();
		float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
		//Scale our height by a factor of 20
		NewLocation.X += DeltaHeight * MovementExtent;
		RunningTime += DeltaTime * MovementSpeed;
		SetActorLocation(NewLocation);
	}
	else
	{
		//Floating part
		FVector NewLocation = GetActorLocation();
		float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
		//Scale our height by a factor of 20
		NewLocation.Z += DeltaHeight * MovementExtent;
		RunningTime += DeltaTime * MovementSpeed;
		SetActorLocation(NewLocation);
	}
}

void AMovingPlatformActor::BeginPlay()
{
	Super::BeginPlay();

	if (IsMovingRight)
	{
		UMovementFunctionLibrary::LockTo2DXY(Box);
	}
	else if (!IsMovingRight)
	{
		UMovementFunctionLibrary::LockTo2DZY(Box);
	}

	if (MovementExtent == 0.0f)
	{
		UMovementFunctionLibrary::LockEverything(Box);
	}
}