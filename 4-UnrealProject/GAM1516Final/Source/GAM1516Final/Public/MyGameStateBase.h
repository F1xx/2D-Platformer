// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class GAM1516FINAL_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	
	void IncrementPlayerDeaths() { playerdeaths++; }
	
	void AddPlayerAmmo(int amount) { playerammo += amount; }
	void SetPlayerAmmo(int amount) { playerammo = amount; }
	void DecrementPlayerAmmo() { playerammo--; }

	void AddPlayerScore(int amount) { playerScore += amount; }
	void RemovePlayerScore(int amount) { playerScore -= amount; }

    UFUNCTION(BlueprintCallable, Category = "PlayerScore")
	int GetPlayerScore() { return playerScore; }

    UFUNCTION(BlueprintCallable, Category = "Ammo")
    int GetPlayerAmmo() { return playerammo; }

    UFUNCTION(BlueprintCallable, Category = "Death")
    int GetPlayerDeaths() { return playerdeaths; }

	void SetCheckPoint(FTransform tansform) { RespawnPoint = tansform; }
	FTransform GetCheckpoint() { return RespawnPoint; }
	void FoundCheckpoint() { bFoundCheckpoint = true; }
	bool DidFindCheckpoint() { return bFoundCheckpoint; }

private:
	int playerdeaths = 0;
	int playerammo = 0;	
	int playerScore = 0;

	FTransform RespawnPoint;

	bool bFoundCheckpoint = false;
};
