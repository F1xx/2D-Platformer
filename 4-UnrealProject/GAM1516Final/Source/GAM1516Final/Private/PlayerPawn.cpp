// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "ProjectileActor.h"
#include "PaperFlipbookComponent.h"
#include "HealthComponent.h"
#include "MyGameStateBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BasePawnMovementComponent.h"
#include "ProjectileActor.h"

// Sets default values
APlayerPawn::APlayerPawn() : Super()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //Create the player's camera. Other pawns don't have a camera
    Cam = CreateDefaultSubobject<UCameraComponent>("Player Follow Camera");
    Cam->SetProjectionMode(ECameraProjectionMode::Orthographic);
    Cam->SetOrthoWidth(720.0f);
    Cam->SetupAttachment(RootComponent);

	HealthComponent->SetCurrentHealth(100.0f);
	MovementComponent->SetOwner(this);

	Capsule->SetCollisionProfileName("BlockEnemy");

    RunSpeed = 200.0f;

    Tags.Add("Player");
}

void APlayerPawn::BeginPlay()
{
    Super::BeginPlay();
}

void APlayerPawn::HurtPlayer()
{
	HealthComponent->TakeDamage(20.0f);
}

void APlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("Bulllettype: %i"), (int)bulletType));

	if (IsShooting)
	{
		Shoot();
	}
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

int APlayerPawn::GetCurrentHealth()
{
    return HealthComponent->GetCurrentHealth();
}

void APlayerPawn::Shoot()
{
	if (CanShoot)
	{
		Super::Shoot();

		CanShoot = false;
		GetWorldTimerManager().SetTimer(SetCanShootTimer, this, &APlayerPawn::SetCanShoot, FireRate, false);
		IsShooting = true;
	}
}

void APlayerPawn::StopShoot()
{
	if (AnimState == EAnimState::Shooting)
	{
		AnimState = EAnimState::Idle;
	}
	SetCanShoot();
	IsShooting = false;
}

//player overrides this to respawn
void APlayerPawn::Die()
{
	m_GameState->IncrementPlayerDeaths();

	if (m_GameState->DidFindCheckpoint())
	{
		Destroy();
		GetWorld()->GetAuthGameMode()->RestartPlayerAtTransform(GetWorld()->GetFirstPlayerController(), m_GameState->GetCheckpoint());
	}
	else
	{
		Destroy();
		GetWorld()->GetAuthGameMode()->RestartPlayer(GetWorld()->GetFirstPlayerController());
	}
}

int APlayerPawn::GetMaxHealth()
{
    return HealthComponent->GetMaxHealth();
}