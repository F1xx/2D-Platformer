// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyBasePawn.generated.h"

UCLASS()
class BREAKOUT_API AMyBasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyBasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = Character, VisibleAnyWhere, meta = (AllowPrivateAccess))
		class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Visual")
		class UPaperSpriteComponent* PawnSprite;

	UPROPERTY(EditAnywhere, Category = "World Camera")
		class UCameraComponent* Cam;

	UPROPERTY(EditAnywhere, Category = "Movement Speed")
		float MoveSpeed;

	void MoveRight(float value);
	void FollowMouse(float value);
    
    UFUNCTION(BlueprintCallable, Category = "Pickups")
        int GetNumOfPoints();

    UFUNCTION(BlueprintCallable, Category = "Status")
        int GetNumOfLives();

    void IncreasePoints(int val);

private:
	float MovementRight;
    int numPoints;
    int numLives;

	float xpos;
};
