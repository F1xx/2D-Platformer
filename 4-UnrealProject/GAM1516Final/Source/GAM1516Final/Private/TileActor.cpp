// Fill out your copyright notice in the Description page of Project Settings.

#include "TileActor.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "MovementFunctionLibrary.h"



// Sets default values
ATileActor::ATileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Flor = CreateDefaultSubobject<UBoxComponent>("FloorComponent");
	Flor->SetEnableGravity(false);
	Flor->SetSimulatePhysics(true);
	Flor->SetNotifyRigidBodyCollision(true);
	Flor->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Flor->SetCollisionObjectType(ECC_WorldStatic);
	Flor->SetCollisionResponseToAllChannels(ECR_Block);
	Flor->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);

    UMovementFunctionLibrary::LockEverything(Flor);

    Wall = CreateDefaultSubobject<UBoxComponent>("WallComponent");
    Wall->SetEnableGravity(false);
    Wall->SetSimulatePhysics(true);
    Wall->SetNotifyRigidBodyCollision(true);
    Wall->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    Wall->SetCollisionObjectType(ECC_WorldStatic);
    Wall->SetCollisionResponseToAllChannels(ECR_Block);
	Wall->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);

    UMovementFunctionLibrary::LockEverything(Wall);
    
    Ceil = CreateDefaultSubobject<UBoxComponent>("CelingComponent");
    Ceil->SetEnableGravity(false);
    Ceil->SetSimulatePhysics(true);
    Ceil->SetNotifyRigidBodyCollision(true);
    Ceil->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    Ceil->SetCollisionObjectType(ECC_WorldStatic);
    Ceil->SetCollisionResponseToAllChannels(ECR_Block);
	Ceil->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);

    UMovementFunctionLibrary::LockEverything(Ceil);

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Component");
	Sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	RootComponent = Sprite;

	Flor->SetupAttachment(RootComponent);
    Wall->SetupAttachment(RootComponent);
    Ceil->SetupAttachment(RootComponent);

	Flor->ComponentTags.Add("Floor");
	Wall->ComponentTags.Add("Wall");
	Ceil->ComponentTags.Add("Ceiling");

    Tags.Add("Tile");
}

void ATileActor::BeginPlay()
{
	//Super::BeginPlay();	
}

// Called every frame
void ATileActor::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);
}

