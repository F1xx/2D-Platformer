// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAM1516FINAL_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Possess(APawn* aPawn) override;
	virtual void UnPossess() override;

protected:
	virtual void SetupInputComponent() override;
	virtual void AcknowledgePossession(APawn* PossesedPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	void MoveRight(float value);
	void Jump();
	void StopJump();
	void Shoot();	
	void StopShoot();
	void HurtPlayer();
};
