// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBasePawn.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "LockMovementFunctionLibrary.h"

#include "BallSpawner.h"

// Sets default values
AMyBasePawn::AMyBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetCollisionProfileName("BlockAll");
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetNotifyRigidBodyCollision(true);
    BoxComponent->SetEnableGravity(false);
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoxComponent->SetLinearDamping(10.0f);
	RootComponent = BoxComponent;

	PawnSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Pawn Visual");
	PawnSprite->SetCollisionProfileName("NoCollision");
	PawnSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PawnSprite->SetGenerateOverlapEvents(false);
	PawnSprite->SetupAttachment(RootComponent);

	Cam = CreateDefaultSubobject<UCameraComponent>("Player Follow Camera");
	Cam->SetProjectionMode(ECameraProjectionMode::Orthographic);
	Cam->SetOrthoWidth(10000.0f);

	Tags.Add("Paddle");

	ULockMovementFunctionLibrary::LockPaddlePhysics(BoxComponent);
	ULockMovementFunctionLibrary::LockPaddlePhysics(PawnSprite);
}

// Called when the game starts or when spawned
void AMyBasePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementRight != 0)
	{
		FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * MovementRight);
		SetActorLocation(NewLocation);
	}

	FVector NewLoc = GetActorLocation();
	NewLoc.X = xpos;



	SetActorLocation(NewLoc);
}

// Called to bind functionality to input
void AMyBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyBasePawn::MoveRight(float value)
{
	MovementRight = value * (1 + MoveSpeed);
}

void AMyBasePawn::FollowMouse(float value)
{
	xpos = value;
}

int AMyBasePawn::GetNumOfPoints()
{
    return numPoints;
}
int AMyBasePawn::GetNumOfLives()
{
    return numLives;
}

void AMyBasePawn::IncreasePoints(int value)
{
    numPoints += value;
}
