// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "EndGameLocationActor.generated.h"

/**
 * 
 */
UCLASS()
class GAM1516FINAL_API AEndGameLocationActor : public ABaseActor
{
	GENERATED_BODY()
	
public:
	AEndGameLocationActor();

	UFUNCTION()//Do not add this first
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	
};
