// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "BasePawn.h"

void AMyPlayerController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);
}

void AMyPlayerController::UnPossess()
{
	Super::UnPossess();
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent != nullptr)
	{
		//Axis
		InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);

		//Action Pressed
		InputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPlayerController::Shoot);
		InputComponent->BindAction("Shoot", IE_Released, this, &AMyPlayerController::StopShoot);
		InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::Jump);
		InputComponent->BindAction("Jump", IE_Released, this, &AMyPlayerController::StopJump);
		InputComponent->BindAction("HurtPlayer", IE_Pressed, this, &AMyPlayerController::HurtPlayer);
	}
}

void AMyPlayerController::AcknowledgePossession(APawn * PossesedPawn)
{
}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMyPlayerController::MoveRight(float value)
{
	ABasePawn* pawn = Cast<ABasePawn>(GetPawn());
	if (pawn)
		pawn->MoveRight(value);
}

void AMyPlayerController::Jump()
{
	ABasePawn* pawn = Cast<ABasePawn>(GetPawn());
	if (pawn)
		pawn->Jump();
}

void AMyPlayerController::StopJump()
{
	ABasePawn* pawn = Cast<ABasePawn>(GetPawn());
	if (pawn)
		pawn->StopJump();
}

void AMyPlayerController::Shoot()
{
	ABasePawn* pawn = Cast<ABasePawn>(GetPawn());
	if (pawn)
		pawn->Shoot();
}

void AMyPlayerController::StopShoot()
{
	ABasePawn* pawn = Cast<ABasePawn>(GetPawn());
	if (pawn)
		pawn->StopShoot();
}

void AMyPlayerController::HurtPlayer()
{
	ABasePawn* pawn = Cast<ABasePawn>(GetPawn());
	if (pawn)
		pawn->HurtPlayer();
}
