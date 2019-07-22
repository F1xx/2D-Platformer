// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "BasePickup.generated.h"

/**
 * 
 */
UCLASS()
class GAM1516FINAL_API ABasePickup : public ABaseActor
{
	GENERATED_BODY()
	
public:
    // Sets default values for this actor's properties
    ABasePickup();
	
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

	float RunningTime;

public:
    UPROPERTY(EditAnywhere, Category = "Float range")
        float FloatRange;
    UPROPERTY(EditAnywhere, Category = "Float range")
        float FloatSpeed;

    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
