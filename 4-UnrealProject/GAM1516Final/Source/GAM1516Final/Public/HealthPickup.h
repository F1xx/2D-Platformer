// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "HealthPickup.generated.h"

/**
 *
 */
UCLASS()
class GAM1516FINAL_API AHealthPickup : public ABasePickup
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AHealthPickup();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()//Do not add this first
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    float RunningTime;


};
