// Fill out your copyright notice in the Description page of Project Settings.

#include "KillPlane.h"
#include "Components/BoxComponent.h"
#include "BallSpawner.h"
#include "BallActor.h"


// Sets default values
AKillPlane::AKillPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box->SetCollisionProfileName("OverlapAll");
	Box->OnComponentBeginOverlap.AddDynamic(this, &AKillPlane::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AKillPlane::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillPlane::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABallActor::StaticClass()))
	{
		ABallSpawner* spawner = Cast<ABallSpawner>(OtherActor->GetOwner());
		spawner->ShouldBeSpawned(true);
	}

	OtherActor->Destroy();
}
