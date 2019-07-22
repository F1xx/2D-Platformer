// Fill out your copyright notice in the Description page of Project Settings.

#include "GAM1516FinalGameModeBase.h"
#include "EngineUtils.h" //Needed for TActorIterator
#include "Kismet/GameplayStatics.h"
#include "MyGameStateBase.h"

void AGAM1516FinalGameModeBase::StartPlay()
{
	Super::StartPlay();
	FString command = "show collision";
	APlayerController* controller =
		UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (controller)
	{
		controller->ConsoleCommand(command, false);
		controller->bShowMouseCursor = true;
		controller->bEnableClickEvents = true;
		controller->bEnableMouseOverEvents = true;
	}
}

void AGAM1516FinalGameModeBase::BeatLevel()
{
	//Hardcoded to open level 2 but this could be used to open chains of levels.
	UGameplayStatics::OpenLevel(this, FName("Level_2"), false);
}