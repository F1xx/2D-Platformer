// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"
#include "MovementFunctionLibrary.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyPlayerController.h"
#include "HealthComponent.h"
#include "MyGameStateBase.h"
#include "BasePawnMovementComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperCharacter.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collision for pawns. Inherited
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	//Capsule->SetCollisionProfileName("BlockAll");
	Capsule->SetEnableGravity(true);
	Capsule->SetSimulatePhysics(true);
	Capsule->SetNotifyRigidBodyCollision(true);
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Capsule->SetCollisionObjectType(ECC_Pawn);
	Capsule->SetCollisionResponseToAllChannels(ECR_Block);

	RootComponent = Capsule;

	//Sprite for Pawns. Inherited
	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(APaperCharacter::SpriteComponentName);
	if (Sprite)
	{
		Sprite->AlwaysLoadOnClient = true;
		Sprite->AlwaysLoadOnServer = true;
		Sprite->bOwnerNoSee = false;
		Sprite->bAffectDynamicIndirectLighting = true;
		Sprite->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Sprite->SetupAttachment(RootComponent);
		Sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Sprite->SetGenerateOverlapEvents(false);
	}

	SetState(EAnimState::Idle);

	MovementComponent = CreateDefaultSubobject<UBasePawnMovementComponent>("Movement Component");
	MovementComponent->bAutoRegister = true;
	MovementComponent->UpdatedComponent = RootComponent;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");

	UMovementFunctionLibrary::LockTo2D(Capsule);

	bulletType = BulletType_Standard;

	Tags.Add("Base Pawn");
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	m_GameState = Cast<AMyGameStateBase>(GetWorld()->GetGameState());

	Capsule->OnComponentHit.AddDynamic(this, &ABasePawn::OnHit);

	if (Sprite != nullptr)
		Sprite->Stop();
}

void ABasePawn::UpdateAnimation()
{
    FVector currVelocity = Capsule->BodyInstance.GetUnrealWorldVelocity();

	switch (AnimState)
	{
	case EAnimState::Idle:
		Sprite->Stop();
		Sprite->SetFlipbook(IdleFlipbook);
		Sprite->SetLooping(true);
		Sprite->Play();
		break;
	case EAnimState::Jumping:
        if (currVelocity.Z > 60)
            Sprite->SetFlipbook(StartJumpFlipbook);
        else if (currVelocity.Z < -60)
            Sprite->SetFlipbook(EndJumpFlipbook);
        else
            Sprite->SetFlipbook(MidJumpFlipbook);
		
        Sprite->SetLooping(true);
		Sprite->Play();
		break;
	case EAnimState::Walking:
		Sprite->SetFlipbook(WalkFlipbook);
		Sprite->SetLooping(true);
		Sprite->Play();
		break;
	case EAnimState::StartShooting:
		break;
	case EAnimState::Shooting:
		Sprite->SetFlipbook(ShootFlipbook);
		Sprite->SetLooping(true);
		Sprite->Play();
		break;
	case EAnimState::Dying:
		break;
	case EAnimState::Dead:
		break;
	case EAnimState::Hit:
		break;
	default:
		break;
	}
}

void ABasePawn::HurtPlayer()
{
	//does nothing in base
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateAnimation();
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasePawn::Shoot()
{
	//make sure template is set
	if (ProjectileTemplate != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			//using the gamestate for ammo because reasons
			if (m_GameState)
			{
				SetState(EAnimState::Shooting);

				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				FTransform SpawnTransform = FTransform(Sprite->GetSocketRotation("Gun"), Sprite->GetSocketLocation("Gun"));
				AProjectileActor* SpawnedActor = World->SpawnActor<AProjectileActor>(ProjectileTemplate, SpawnTransform, SpawnParams);
				//if we spawned correctly
				if (SpawnedActor)
				{
					FVector direction = FRotationMatrix(SpawnTransform.Rotator()).GetScaledAxis(EAxis::X);
					SpawnedActor->SetBulletType(bulletType);
						
					if (this->ActorHasTag("Player") && bulletType != BulletType_Standard)
					{
						m_GameState->DecrementPlayerAmmo();

						//if we just shot the last special ammo reset to standard ammo
						if (m_GameState->GetPlayerAmmo() <= 0)
						{
							bulletType = BulletType_Standard;
							m_GameState->SetPlayerAmmo(0);
						}
					}
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Failed to get Gamestate");
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Projectile Template Not Set");
	}
}

void ABasePawn::StopShoot()
{
	if (AnimState == EAnimState::Shooting)
	{
		AnimState = EAnimState::Idle;
	}
}

//Damages the pawn. Call with a negative value to heal
float ABasePawn::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return HealthComponent->TakeDamage(Damage);
}

UPawnMovementComponent * ABasePawn::GetMovementComponent() const
{
	return MovementComponent;
}


void ABasePawn::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
    //Start of Capsule to Capsule collision
    /*UCapsuleComponent* Capsuley = Cast<UCapsuleComponent>(OtherActor);
    FVector tileSize;
    tileSize = Capsuley->GetScaledCapsuleExtent();
    float rad;
    float height;
    Capsule->GetScaledCapsuleSize(rad, height);*/

    TArray<UActorComponent*> collisions;
    OtherActor->GetComponents(collisions);

    //GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Purple, collisions[0]);
    if (OtherActor->ActorHasTag("Tile"))
    {
        if (OtherComponent->ComponentHasTag("Wall") == true)
        {
          //  GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, "Wall");
        }
        if (OtherComponent->ComponentHasTag("Floor") == true)
        {
          //  GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, "Floor");
			MovementComponent->SetOnFloor(true);
            MovementComponent->StopJump();
			MovementComponent->SetCanJump(true);
			Land();
        }
        if (OtherComponent->ComponentHasTag("Ceiling") == true)
        {
           // GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Purple, "Celing");
			MovementComponent->StopJump();
        }
		else //for debug
		{
			//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, "FAKE FLOOR");
			MovementComponent->SetOnFloor(true);
			MovementComponent->StopJump();
			MovementComponent->SetCanJump(true);
			Land();
		}
    }
    else
    {
      // GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "NotTile");
 		MovementComponent->SetOnFloor(true);
		MovementComponent->StopJump();
		MovementComponent->SetCanJump(true);
		Land();
    }
}


//a function that by default destroys the pawn. Overwrite to have a better death stuff
void ABasePawn::Die()
{
	Destroy();
}

void ABasePawn::MoveRight(float value)
{
	if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
	{
		MovementComponent->MoveRight(value, RunSpeed);

        if ((AnimState == EAnimState::Idle || AnimState == EAnimState::Walking) && AnimState != EAnimState::Shooting)
        {
            if (value == 0.0f)
            {
                SetState(EAnimState::Idle);
            }
            else
            {
                SetState(EAnimState::Walking);
            }
        }
	}
}

void ABasePawn::Jump()
{
	if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
	{
		MovementComponent->Jump();
		if (AnimState == EAnimState::Walking || AnimState == EAnimState::Idle)
			SetState(EAnimState::Jumping);
	}
}

void ABasePawn::StopJump()
{
	if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
	{
		MovementComponent->StopJump();
	}
}

void ABasePawn::Land()
{
    if (AnimState == EAnimState::Dead)
        SetState(EAnimState::Dead);
    else if (AnimState != EAnimState::Shooting)
    {
		SetState(EAnimState::Idle);
    }
}

void ABasePawn::Disable()
{
	SetActorHiddenInGame(true);
	Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);
}

//ICA4: UnHide this actor in game, and enable collision (Look up documentation)
void ABasePawn::Enable()
{
	SetActorHiddenInGame(false);
	Capsule->SetCollisionResponseToAllChannels(ECR_Block);
}

void ABasePawn::SetState(EAnimState newstate)
{
	AnimState = newstate;
}
