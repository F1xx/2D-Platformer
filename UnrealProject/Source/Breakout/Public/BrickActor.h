// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBaseActor.h"
#include "BrickActor.generated.h"

/**
 * 
 */
UCLASS()
class BREAKOUT_API ABrickActor : public AMyBaseActor
{
	GENERATED_BODY()
	
public:
	ABrickActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
