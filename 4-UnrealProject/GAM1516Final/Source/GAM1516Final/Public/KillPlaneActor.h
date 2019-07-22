// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "KillPlaneActor.generated.h"

/**
 * 
 */
UCLASS()
class GAM1516FINAL_API AKillPlaneActor : public ABaseActor
{
	GENERATED_BODY()

public:
		AKillPlaneActor();

		UFUNCTION()//Do not add this first
			void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
