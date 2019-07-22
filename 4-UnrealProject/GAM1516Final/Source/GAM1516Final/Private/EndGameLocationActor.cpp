// Fill out your copyright notice in the Description page of Project Settings.

#include "EndGameLocationActor.h"
#include "GAM1516FinalGameModeBase.h"
#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "GAM1516FinalGameModeBase.h"

AEndGameLocationActor::AEndGameLocationActor()
{
	Tags.Add("EndPoint");
	Box->OnComponentBeginOverlap.AddDynamic(this, &AEndGameLocationActor::OnOverlapBegin);

	//Box->SetCollisionObjectType(ECC_WorldStatic);
	Box->SetCollisionResponseToAllChannels(ECR_Overlap);//
	Box->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
}

void AEndGameLocationActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		APlayerPawn* playerPawn = Cast<APlayerPawn>(OtherActor);
		if (playerPawn)
		{
			AGAM1516FinalGameModeBase* thismode = Cast<AGAM1516FinalGameModeBase>(GetWorld()->GetAuthGameMode());

			if (thismode)
			{
				thismode->BeatLevel();
			}
		}
	}
}

void AEndGameLocationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEndGameLocationActor::BeginPlay()
{
	Super::BeginPlay();
}