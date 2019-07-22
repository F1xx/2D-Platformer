// Fill out your copyright notice in the Description page of Project Settings.

#include "GroundEnemyPawn.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Public/GroundEnemyPawn.h"
#include "PaperSpriteComponent.h"
#include "ProjectileActor.h"
#include "Components/ArrowComponent.h"
#include "BasePawnMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "PlayerPawn.h"

AGroundEnemyPawn::AGroundEnemyPawn() : Super()
{
    Capsule->BodyInstance.bLockZRotation = true;
    Tags.Empty();
	Tags.Add("Enemy");
	Tags.Add("GroundEnemy");

    HealthComponent->SetCurrentHealth(20.0f);
    CurrentPatrolPoint = FirstPatrolPoint;
	MovementComponent->SetOwner(this);
	bulletType = BulletType_Fast;

	Capsule->SetCollisionProfileName("BlockPlayer");

    RunSpeed = 100.0f;

	//AI DETECTION
	Detection = CreateDefaultSubobject<UPawnSensingComponent>("Pawn Detection");
}

void AGroundEnemyPawn::Tick(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, FString::Printf(TEXT("Ground Enemy Health: %f"), HealthComponent->currentHealth));
    
	if (isPatrolling)
	{
		float direction = 0;

		if (CurrentPatrolPoint)
		{
			if (CurrentPatrolPoint->GetActorLocation().X - GetActorLocation().X < 0) //if its left
			{
				direction = -1.0f;
			}
			else
			{
				direction = 1.0f;
			}

			MovementComponent->MoveRight(direction, RunSpeed);

			float dist = CurrentPatrolPoint->GetDistanceTo(this);
			if (dist < 20.0f)
			{
				MoveToNextPatrolPoint();
			}
		}
		else
		{
			MoveToNextPatrolPoint();
		}
	}
 	else
 	{
 		if (m_Target)
 		{
 			//AI MOVEMENT
 			isPatrolling = !Detection->HasLineOfSightTo(m_Target); //if we have LOS to the player don't go back to patrol
 
 			float direction = 0;
 			if (m_Target->GetActorLocation().X - GetActorLocation().X < 0) //if its left
 			{
 				direction = -1.0f;
 			}
 			else
 			{
 				direction = 1.0f;
 			}

			//stop the enemyt from just walking into us
			float dist = m_Target->GetDistanceTo(this);
			if (dist > 60.0f)
			{
				MovementComponent->MoveRight(direction, RunSpeed);
			}
 
			Shoot();
 		}
 		else
 		{
 			isPatrolling = true;
 		}
 	}
}

void AGroundEnemyPawn::Shoot()
{
	if (CanShoot)
	{
		Super::Shoot();

		CanShoot = false;
		GetWorldTimerManager().SetTimer(SetCanShootTimer, this, &AGroundEnemyPawn::SetCanShoot, FireTimerDelay, false);
	}
}

void AGroundEnemyPawn::BeginPlay()
{
    Super::BeginPlay();
}

void AGroundEnemyPawn::MoveToNextPatrolPoint()
{
    if (CurrentPatrolPoint)
    {
        if (CurrentPatrolPoint == FirstPatrolPoint)
        {
            CurrentPatrolPoint = SecondPatrolPoint;
        }
        else
        {
            CurrentPatrolPoint = FirstPatrolPoint;
        }
    }
    else
        CurrentPatrolPoint = FirstPatrolPoint;
}

void AGroundEnemyPawn::OnSeePawn(APawn *OtherPawn)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "See Pawn: " + OtherPawn->GetName());

	m_Target = Cast<APlayerPawn>(OtherPawn);

	if (m_Target)
	{
		isPatrolling = false;
	}
}

void AGroundEnemyPawn::OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume)
{
	//do nothing
}

void AGroundEnemyPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Detection->OnSeePawn.AddDynamic(this, &AGroundEnemyPawn::OnSeePawn);
	Detection->bOnlySensePlayers = true;
	Detection->SightRadius = DetectionRage;
	Detection->SensingInterval = 0.25f; //4times per second
}
