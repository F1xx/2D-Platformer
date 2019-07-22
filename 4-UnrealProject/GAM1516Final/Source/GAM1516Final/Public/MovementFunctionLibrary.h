// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MovementFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAM1516FINAL_API UMovementFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:
	static void LockEverything(class UPrimitiveComponent* primitive);
	static void LockTo2D(class UPrimitiveComponent* primitive);
	static void LockTo2DXY(class UPrimitiveComponent* primitive);
	static void LockTo2DZY(class UPrimitiveComponent* primitive);
	
};
