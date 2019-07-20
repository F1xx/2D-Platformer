// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakoutGameModeBase.h"
#include "EngineUtils.h" //Needed for TActorIterator
#include "Kismet/GameplayStatics.h"


void ABreakoutGameModeBase::StartPlay()
{
	Super::StartPlay();
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green,
			"Actor: " + ActorItr->GetName());
	}
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
