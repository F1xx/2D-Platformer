// Fill out your copyright notice in the Description page of Project Settings.

#include "BallActor.h"
#include "Components/SphereComponent.h"
#include "BallBounceComponent.h"
#include "GameFramework/MovementComponent.h"
#include "LockMovementFunctionLibrary.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"


// Sets default values
ABallActor::ABallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent* comp = Cast<UBoxComponent>(GetComponentByClass(UBoxComponent::StaticClass()));
	if (comp)
	{
		comp->DestroyComponent();
		comp->SetActive(false);
	}

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	Sphere->SetCollisionProfileName("BlockAll");

	RootComponent = Sprite;
	Sphere->SetupAttachment(Sprite);

	//This code is what makes the ball bounce and stuff
	Projectile = CreateDefaultSubobject<UBallBounceComponent>("Projectile Movement Component");
	Projectile->bShouldBounce = true;
	Projectile->Bounciness = 1.0f;
	Projectile->ProjectileGravityScale = 0.0f;
	Projectile->Friction = 0.0f;
	Projectile->InitialSpeed = 3000.0f;
	TotalSpeed = Projectile->InitialSpeed;

	ULockMovementFunctionLibrary::LockBallPhysics(Sprite);
}

// Called when the game starts or when spawned
void ABallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TotalSpeed += DeltaTime * ProjectileSpeedIncrement;
	FVector x = Projectile->Velocity.GetSafeNormal() * TotalSpeed;
	Projectile->Velocity = x;

	FVector loc = GetActorLocation();
	loc.Y = 0.0f;
	SetActorLocation(loc);

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, "Speed: " + FString::SanitizeFloat(TotalSpeed));
}

class UPrimitiveComponent* ABallActor::GetPhysicsComponent()
{
	return Cast<UPrimitiveComponent>(Sprite);
}

