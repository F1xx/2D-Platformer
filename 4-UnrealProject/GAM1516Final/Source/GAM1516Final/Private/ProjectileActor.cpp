// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "BulletMovementComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "BasePawn.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "ConstructorHelpers.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "PlayerPawn.h"


AProjectileActor::AProjectileActor() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("Projectile");

	Lifelength = 0.5f;
	bulletType = BulletType_Standard;

	ConstructComponents();

	Sprites[0] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("/Game/Sprites/prj_Blaster_Sprite")).Object;
	Sprites[1] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("/Game/Sprites/Prj_Orb_Sprite")).Object;
	Sprites[2] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("/Game/Sprites/Prj_Pierce_Sprite")).Object;
	Sprites[3] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("/Game/Sprites/Prj_Missile_Sprite")).Object;
}

//Set a custom lifelength for the projectile
AProjectileActor::AProjectileActor(float lifelength, BulletType type) : Super()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("Projectile");

	Lifelength = lifelength;
	bulletType = type;

	ConstructComponents();
}

void AProjectileActor::ConstructComponents()
{
	//remove the box component gained from BaseActor and replace with a sphere
	UBoxComponent* comp = Cast<UBoxComponent>(GetComponentByClass(UBoxComponent::StaticClass()));
	if (comp)
	{
		comp->DestroyComponent();
		comp->SetActive(false);
	}

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere Component");

	RootComponent = Sphere;
	Sprite->SetupAttachment(Sphere);

	//Create a bullet and set its settings
	Projectile = CreateDefaultSubobject<UBulletMovementComponent>("Projectile Movement Component");
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion'"));
	if (PS.Succeeded())
	{
		ProjectileFX = PS.Object;
	}

	Sphere->SetCollisionProfileName("ProjectilePreset");

	ABasePawn* pawn = Cast<ABasePawn>(GetOwner());
	if (pawn)
	{
		SetBulletType(pawn->GetBulletType());
	}
	else
	{
		SetBulletType(bulletType);
	}
}

void AProjectileActor::ResetBullet()
{
	Projectile->InitialSpeed = 3000.0f;
	Projectile->bShouldBounce = false;
	Projectile->Bounciness = 0.0f;
	Projectile->Friction = 0.1f;
	Projectile->ProjectileGravityScale = 0.0f;
	Lifelength = 1.0f;
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Overlap); //player
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECR_Overlap); //enemy
}

void AProjectileActor::SetBulletType(TEnumAsByte<BulletType> type)
{
	bulletType = type;

	ResetBullet();

	int index = 0;

	switch (type)
	{
	case BulletType_Standard:
		Projectile->InitialSpeed = 1000.0f;
		Projectile->ProjectileGravityScale = 0.2f;
		index = 0;
		break;
	case BulletType_Fast:
		Projectile->InitialSpeed = 3000.0f;
		Projectile->ProjectileGravityScale = 0.1f;
		index = 0;
		break;
	case BulletType_Slow:
		Projectile->InitialSpeed = 200.0f;
		Projectile->ProjectileGravityScale = 0.1f;
		index = 3;
		break;
	case BulletType_Bouncy:
		Projectile->InitialSpeed = 600.0f;
		Projectile->bShouldBounce = true;
		Projectile->Bounciness = 1.0f;
		Projectile->BounceAdditionalIterations = 12;
		Projectile->Friction = 0.1f;
		Projectile->ProjectileGravityScale = 0.9f;
		Lifelength = 1.5f;
		index = 1;
		Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECR_Block); //enemy

		break;
	case BulletType_Piercing:
		Projectile->InitialSpeed = 1000.0f;
        Sphere->SetCollisionObjectType(ECC_WorldStatic);
		index = 2;
		break;
	default:
		break;
	}

	Sprite->SetSprite(Sprites[index]);
}

void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	//Upon being created start the timer that will destroy itself upon completion
	GetWorldTimerManager().SetTimer(DeathTimer, this, &AProjectileActor::Die, Lifelength, false);
	Sphere->OnComponentHit.AddDynamic(this, &AProjectileActor::OnHit);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectileActor::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AProjectileActor::OnOverlapEnd);
}

void AProjectileActor::HandleCollision(class UPrimitiveComponent* hitcomp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, const FHitResult & Hit)
{
	//Make sure the other actor is a pawn
	ABasePawn* pawn = Cast<ABasePawn>(OtherActor);

	if (pawn)
	{
		//basically if the last tag of what this hit is the same as who fired this projectile don't cause damage.
		if (OtherActor->Tags.Last() != GetOwner()->Tags.Last())
		{
			TSubclassOf<UDamageType> P;

			FHitResult HitInfo;

			UGameplayStatics::ApplyPointDamage(OtherActor, 10.0f, GetActorLocation(), HitInfo, nullptr, this, P);
			UGameplayStatics::SpawnEmitterAtLocation(this, ProjectileFX, GetActorLocation());

			//Destroy itself because it hit a pawn
			if (bulletType != BulletType_Bouncy && bulletType != BulletType_Piercing)
			{
				Die();
			}
		}
	}
	else if (OtherActor->ActorHasTag("Tile") || OtherActor->ActorHasTag("Base Actor"))
	{
		if (bulletType != BulletType_Bouncy)
		{
			Die();
			UGameplayStatics::SpawnEmitterAtLocation(this, ProjectileFX, GetActorLocation());
		}
	}
	else
	{
		return;
	}
}

void AProjectileActor::Die()
{
	Destroy();
}

void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileActor::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	HandleCollision(HitComponent, OtherActor, OtherComponent, Hit);
}

void AProjectileActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	HandleCollision(OverlappedComp, OtherActor, OtherComp, SweepResult);
}

void AProjectileActor::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	//nothing as of yet
}
