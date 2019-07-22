// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "ProjectileActor.h"
#include "PlayerPawn.generated.h"

/**
 * 
 */
UCLASS()
class GAM1516FINAL_API APlayerPawn : public ABasePawn
{
	GENERATED_BODY()
public:
	APlayerPawn();
	
	UPROPERTY(EditAnywhere, Category = "World Camera")
		class UCameraComponent* Cam;	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HurtPlayer() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    int GetMaxHealth();

    int GetCurrentHealth();

	virtual void Shoot() override;
	virtual void StopShoot() override;

	FTimerHandle SetCanShootTimer;

	//Lower = Faster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
		float FireRate = 0.25f;

	bool CanShoot = true;
	bool IsShooting = false;
	void SetCanShoot() { CanShoot = true; }

	class AMyGameStateBase* GetGameState() { return m_GameState; }

	UFUNCTION()
	virtual void Die() override;


    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercentage() { return (float)GetCurrentHealth() / 100.0f; }
};
