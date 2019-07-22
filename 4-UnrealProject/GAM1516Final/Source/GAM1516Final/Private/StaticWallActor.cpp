// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticWallActor.h"
#include "Components/BoxComponent.h"
#include "MovementFunctionLibrary.h"


AStaticWallActor::AStaticWallActor()
{
	UMovementFunctionLibrary::LockEverything(Box);

	Tags.Add("Placeholder");
	Tags.Add("Tile");

	Box->SetCollisionObjectType(ECC_WorldStatic);
	Box->SetCollisionResponseToAllChannels(ECR_Block);
}

