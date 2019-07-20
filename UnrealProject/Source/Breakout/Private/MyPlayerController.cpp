// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "MyBasePawn.h"


void AMyPlayerController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, "AMyPlayerController::Possess: - " + aPawn->GetName());
}

void AMyPlayerController::UnPossess()
{
	APawn* posessedPawn = Cast<APawn>(GetOwner());
	if (posessedPawn)
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, "AMyPlayerController::UnPossess: - " + GetOwner()->GetName());

	Super::UnPossess();
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent != nullptr)
	{
		InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);
	}
}

void AMyPlayerController::AcknowledgePossession(APawn* PossesedPawn)
{

}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	float x, y;
	GetMousePosition(x, y);

	FVector worldpos, dir;
	DeprojectMousePositionToWorld(worldpos, dir);

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, FString::SanitizeFloat(worldpos.X));

	if (worldpos.X < -2200)
		worldpos.X = -2200;
	else if (worldpos.X > 2200)
		worldpos.X = 2200;

	AMyBasePawn* pawn = Cast<AMyBasePawn>(GetPawn());
	if (pawn)
		pawn->FollowMouse(worldpos.X);
}

void AMyPlayerController::MoveRight(float value)
{
	AMyBasePawn* pawn = Cast<AMyBasePawn>(GetPawn());
	if (pawn)
		pawn->MoveRight(value);
	
}
