// Fill out your copyright notice in the Description page of Project Settings.

#include "LockMovementFunctionLibrary.h"

void ULockMovementFunctionLibrary::LockAllPhysics(UPrimitiveComponent * primitive)
{
	primitive->GetBodyInstance()->bLockXRotation = true;
	primitive->GetBodyInstance()->bLockYRotation = true;
	primitive->GetBodyInstance()->bLockZRotation = true;

	primitive->GetBodyInstance()->bLockXTranslation = true;
	primitive->GetBodyInstance()->bLockYTranslation = true;
	primitive->GetBodyInstance()->bLockZTranslation = true;
}

void ULockMovementFunctionLibrary::LockBallPhysics(UPrimitiveComponent * primitive)
{
	primitive->GetBodyInstance()->bLockXRotation = true;
	primitive->GetBodyInstance()->bLockYRotation = true;
	primitive->GetBodyInstance()->bLockZRotation = true;

	primitive->GetBodyInstance()->bLockYTranslation = true;
}

void ULockMovementFunctionLibrary::LockPaddlePhysics(UPrimitiveComponent * primitive)
{
	primitive->GetBodyInstance()->bLockXRotation = true;
	primitive->GetBodyInstance()->bLockYRotation = true;
	primitive->GetBodyInstance()->bLockZRotation = true;

	primitive->GetBodyInstance()->bLockYTranslation = true;
	primitive->GetBodyInstance()->bLockZTranslation = true;
}
