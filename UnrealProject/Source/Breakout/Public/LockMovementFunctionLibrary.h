// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LockMovementFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BREAKOUT_API ULockMovementFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:
	static void LockAllPhysics(class UPrimitiveComponent* primitive);
	static void LockBallPhysics(class UPrimitiveComponent* primitive);
	static void LockPaddlePhysics(class UPrimitiveComponent* primitive);
	
};
