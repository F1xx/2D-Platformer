// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBaseActor.h"
#include "BallActor.generated.h"

UCLASS()
class BREAKOUT_API ABallActor : public AMyBaseActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Actor Strings")
		FName mystring;

	UPROPERTY(EditAnywhere, Category = "Collision Sphere")
		class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, Category = "Projectile Movement")
		class UBallBounceComponent* Projectile;

		float TotalSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Projectile Speed Increment")
		float ProjectileSpeedIncrement = 30.0f;

	class UPrimitiveComponent* GetPhysicsComponent();
	
};
