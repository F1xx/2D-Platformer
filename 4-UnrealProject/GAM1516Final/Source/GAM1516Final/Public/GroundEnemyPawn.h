// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "GroundEnemyPawn.generated.h"

/**
 * 
 */
UCLASS()
class GAM1516FINAL_API AGroundEnemyPawn : public ABasePawn
{
	GENERATED_BODY()
public:
		AGroundEnemyPawn();

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
            float FireTimerDelay = 1.0f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
			float DetectionRage = 300.0f;

        FTimerHandle SetCanShootTimer;

		virtual void Tick(float DeltaTime) override;  

		virtual void Shoot() override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    /* Let the guard go on patrol */
    UPROPERTY(EditInstanceOnly, Category = "AI")
        bool bPatrol;

    /* First of two patrol points to patrol between */
    UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
        AActor* FirstPatrolPoint;

    /* Second of two patrol points to patrol between */
    UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
        AActor* SecondPatrolPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UPawnSensingComponent* Detection;

    // The current point the actor is either moving to or standing at
    AActor* CurrentPatrolPoint;

    UFUNCTION() //WIthout this, the function will be inlined and optimized out
        void MoveToNextPatrolPoint();

	UFUNCTION()
		void OnSeePawn(APawn *OtherPawn);

	UFUNCTION()
		void OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume);

	virtual void PostInitializeComponents() override;

private:
	bool isPatrolling = true;

	class ABasePawn* m_Target;

	bool CanShoot = true;
	void SetCanShoot() { CanShoot = true; }
};
