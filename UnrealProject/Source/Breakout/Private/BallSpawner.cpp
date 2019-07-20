// Fill out your copyright notice in the Description page of Project Settings.

#include "BallSpawner.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"
#include "BallActor.h"
#include "MyBasePawn.h"

// Sets default values
ABallSpawner::ABallSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//delete the box
	UBoxComponent* comp = Cast<UBoxComponent>(GetComponentByClass(UBoxComponent::StaticClass()));
	if (comp)
	{
		comp->DestroyComponent();
		comp->SetActive(false);
	}

	/* arrow component  */
	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(RootComponent);
	SpawnPoint->ArrowSize = 5.f;
	SpawnPoint->SetRelativeRotation(FRotator(50.f, 0.f, 0.f));
	SpawnPoint->SetRelativeLocation(FVector(0.f, 100.f, 0.f));

	ShouldSpawn = true;
}

// Called when the game starts or when spawned
void ABallSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ABallSpawner::SpawnActor, SpawnDelay, true);
	// SpawnTimer can now be reused for any other Timer.
	//GetWorldTimerManager().ClearTimer(SpawnTimer);
	
}

// Called every frame
void ABallSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ABallSpawner::ShouldBeSpawned(bool spawn)
{
	ShouldSpawn = spawn;
}

void ABallSpawner::SpawnActor()
{
	if (ShouldSpawn)
	{
		if (BallActorTemplate != nullptr)
		{
			UWorld* const World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				FTransform SpawnTransform = SpawnPoint->GetComponentTransform();
				ABallActor* SpawnedActor = World->SpawnActor<ABallActor>(BallActorTemplate, SpawnTransform, SpawnParams);
				if (SpawnedActor)
				{
					FVector direction = FRotationMatrix(SpawnTransform.Rotator()).GetScaledAxis(EAxis::X);
					SpawnedActor->SetOwner(this);
				}
			}
			ShouldSpawn = false;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Failed to spawn");
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Won't Spawn");
	}
}
