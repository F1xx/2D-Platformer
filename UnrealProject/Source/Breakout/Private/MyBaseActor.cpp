// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBaseActor.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
AMyBaseActor::AMyBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Actor Visual");
	RootComponent = Sprite;

	Box = CreateDefaultSubobject<UBoxComponent>("Box Component");
	Box->SetCollisionProfileName("BlockAll");
	Box->SetupAttachment(Sprite);
	Box->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AMyBaseActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

class UPrimitiveComponent* AMyBaseActor::GetPhysicsComponent()
{
	return Cast<UPrimitiveComponent>(Sprite);
}

