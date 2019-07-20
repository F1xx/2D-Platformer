// Fill out your copyright notice in the Description page of Project Settings.

#include "BrickActor.h"
#include "BallActor.h"
#include "MyBasePawn.h"
#include "Engine/World.h"
#include "MyPlayerController.h"

#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "LockMovementFunctionLibrary.h"



ABrickActor::ABrickActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ULockMovementFunctionLibrary::LockAllPhysics(Sprite);

	Box->SetNotifyRigidBodyCollision(true);
	Sprite->OnComponentHit.AddDynamic(this, &ABrickActor::OnHit);
}

void ABrickActor::BeginPlay()
{
}

void ABrickActor::Tick(float DeltaTime)
{

}


void ABrickActor::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor)
	{
		if (OtherActor->IsA(ABallActor::StaticClass()))
		{
            //AMyBasePawn* target = Cast<AMyBasePawn>(AMyBasePawn::StaticClass()));
            AMyPlayerController* c = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
            AMyBasePawn* pawn = Cast<AMyBasePawn>(c->GetPawn());
            pawn->IncreasePoints(10);
            //target->IncreasePoints(10);

            Destroy();

			//Code here for updating the HUD

		}
	}
}