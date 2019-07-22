// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseActor.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "MovementFunctionLibrary.h"

// Sets default values
ABaseActor::ABaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	Box->SetEnableGravity(true);
	Box->SetSimulatePhysics(true);
	Box->SetNotifyRigidBodyCollision(true);
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Box->SetCollisionObjectType(ECC_PhysicsBody);
	Box->SetCollisionResponseToAllChannels(ECR_Block);

	RootComponent = Box;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Component");
	Sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Sprite->SetupAttachment(RootComponent);

	UMovementFunctionLibrary::LockTo2D(Box);

	Tags.Add("BaseActor");
}

// Called when the game starts or when spawned
void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

