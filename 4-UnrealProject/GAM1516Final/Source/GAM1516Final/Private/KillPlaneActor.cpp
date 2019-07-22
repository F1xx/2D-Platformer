// Fill out your copyright notice in the Description page of Project Settings.

#include "KillPlaneActor.h"
#include "Components/BoxComponent.h"
#include "BasePawn.h"

AKillPlaneActor::AKillPlaneActor() : Super()
{
	Tags.Add("KillPlane");
	Box->OnComponentBeginOverlap.AddDynamic(this, &AKillPlaneActor::OnOverlapBegin);

	Box->SetCollisionObjectType(ECC_WorldStatic);
	Box->SetCollisionResponseToAllChannels(ECR_Overlap);

	Box->SetEnableGravity(false);
	Box->SetSimulatePhysics(true);
	Box->SetNotifyRigidBodyCollision(true);
}

void AKillPlaneActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor)
	{
		ABasePawn* pawn = Cast<ABasePawn>(OtherActor);
		if (pawn)
		{
			pawn->Die();
		}
		else
		{
			OtherActor->Destroy();
		}
	}
}

