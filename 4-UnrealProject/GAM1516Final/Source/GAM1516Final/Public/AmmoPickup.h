// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "AmmoPickup.generated.h"

/**
*
*/
UCLASS()
class GAM1516FINAL_API AAmmoPickup : public ABasePickup
{
    GENERATED_BODY()

public:
    AAmmoPickup();

    virtual void Tick(float DeltaTime) override;

    virtual void BeginPlay() override;

    UFUNCTION()//Do not add this first
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
        int AmmoValue = 5;
};
