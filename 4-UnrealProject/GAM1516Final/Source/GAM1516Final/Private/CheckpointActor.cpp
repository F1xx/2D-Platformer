// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckpointActor.h"
#include "Components/BoxComponent.h"
#include "PlayerPawn.h"
#include "MyGameStateBase.h"
#include "ConstructorHelpers.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "PaperSpriteComponent.h"

ACheckpointActor::ACheckpointActor() : Super()
{
	Tags.Add("Checkpoint");
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointActor::OnOverlapBegin);

	//Box->SetCollisionObjectType(ECC_WorldStatic);
	Box->SetCollisionResponseToAllChannels(ECR_Overlap);
	Box->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	Sprites[0] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("/Game/Sprites/CheckpointOFF_Sprite")).Object;
	Sprites[1] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("/Game/Sprites/CheckpointON_Sprite")).Object;
}

void ACheckpointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACheckpointActor::BeginPlay()
{
	Super::BeginPlay();
	Sprite->SetSprite(Sprites[0]);
}

void ACheckpointActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (!isActivated)
	{
		if (OtherActor)
		{
			APlayerPawn* playerPawn = Cast<APlayerPawn>(OtherActor);
			if (playerPawn)
			{
				isActivated = true;
				playerPawn->GetGameState()->SetCheckPoint(GetActorTransform());
				playerPawn->GetGameState()->FoundCheckpoint();

				//change sprite
				Sprite->SetSprite(Sprites[1]);
			}
		}
	}
}