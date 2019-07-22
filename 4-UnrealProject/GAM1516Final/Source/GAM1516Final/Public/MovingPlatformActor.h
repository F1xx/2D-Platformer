// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "MovingPlatformActor.generated.h"

/**
 * 
 */
UCLASS()
class GAM1516FINAL_API AMovingPlatformActor : public ABaseActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatformActor();

	virtual void Tick(float DeltaTime) override;

	//true for horizontal, false for vertical
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool IsMovingRight = true;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementExtent = 80.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementSpeed = 2.0f;

protected:
	virtual void BeginPlay() override;

	float RunningTime;	
};
