// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementFunctionLibrary.h"

//Locks X & Z rotation and Y translation
void UMovementFunctionLibrary::LockTo2D(class UPrimitiveComponent* primitive)
{
	primitive->GetBodyInstance()->bLockXRotation = true;
	primitive->GetBodyInstance()->bLockZRotation = true;
	primitive->GetBodyInstance()->bLockYRotation = true;

	primitive->GetBodyInstance()->bLockYTranslation = true;
}

void UMovementFunctionLibrary::LockTo2DXY(UPrimitiveComponent * primitive)
{
	primitive->GetBodyInstance()->bLockXRotation = true;
	primitive->GetBodyInstance()->bLockZRotation = true;
	primitive->GetBodyInstance()->bLockYRotation = true;

	primitive->GetBodyInstance()->bLockYTranslation = true;
	primitive->GetBodyInstance()->bLockXTranslation = true;
	primitive->GetBodyInstance()->bLockTranslation = true;
}

void UMovementFunctionLibrary::LockTo2DZY(UPrimitiveComponent * primitive)
{
	primitive->GetBodyInstance()->bLockXRotation = true;
	primitive->GetBodyInstance()->bLockZRotation = true;
	primitive->GetBodyInstance()->bLockYRotation = true;

	primitive->GetBodyInstance()->bLockYTranslation = true;
	primitive->GetBodyInstance()->bLockZTranslation = true;
	primitive->GetBodyInstance()->bLockTranslation = true;
}

//Locks all rotation and translation
void UMovementFunctionLibrary::LockEverything(class UPrimitiveComponent* primitive)
{
	primitive->GetBodyInstance()->bLockXRotation = true;
	primitive->GetBodyInstance()->bLockYRotation = true;
	primitive->GetBodyInstance()->bLockZRotation = true;

	primitive->GetBodyInstance()->bLockXTranslation = true;
	primitive->GetBodyInstance()->bLockYTranslation = true;
	primitive->GetBodyInstance()->bLockZTranslation = true;
}
