// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "ProjectileActor.h"
#include "BulletPickup.generated.h"


/**
 *
 */
UCLASS()
class GAM1516FINAL_API ABulletPickup : public ABasePickup
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABulletPickup();

    /*UPROPERTY(EditAnywhere, Category = "Bullet Type")
        TEnumAsByte<BulletType> m_BulletType;*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Bullet Type")
        TEnumAsByte<BulletType> Bullet_Type;

    UPROPERTY(EditAnywhere, Category = "Ammo")
        int AmmoAmount;

	virtual void Tick(float DeltaTime) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()//Do not add this first
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
public:

};
