// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileActor.generated.h"



UCLASS()
class GAM1516FINAL_API ATileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Collision")
		class UBoxComponent* Flor;
    UPROPERTY(EditAnywhere, Category = "Collision")
        class UBoxComponent* Wall;
    UPROPERTY(EditAnywhere, Category = "Collision")
        class UBoxComponent* Ceil;	

	UPROPERTY(EditAnywhere, Category = "Actor Visual")
		class UPaperSpriteComponent* Sprite;
};
