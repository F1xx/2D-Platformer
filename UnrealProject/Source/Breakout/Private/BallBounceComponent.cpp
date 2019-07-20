// Fill out your copyright notice in the Description page of Project Settings.

#include "BallBounceComponent.h"
#include "MyBasePawn.h"

// Sets default values for this component's properties
UBallBounceComponent::UBallBounceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBallBounceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBallBounceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FVector UBallBounceComponent::ComputeBounceResult(const FHitResult& Hit, float TimeSlice, const FVector& MoveDelta)
{
	FVector TempVelocity = Velocity;
	AActor* actor = Hit.GetActor();

	TempVelocity = Super::ComputeBounceResult(Hit, TimeSlice, MoveDelta);

	if (actor)
	{
		//if we hit a paddle do this collision
		if (actor->ActorHasTag("Paddle"))
		{
			FVector hitLoc = Hit.Location;
			FVector orig, ending;

			//actor->GetActorBounds(true, orig, ending);

			////Find how far from the left side of the paddle the ball hit
			//float sourceX = abs(hitLoc.X - orig.X);
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(sourceX));

			//sourceX /= (ending.X - orig.X);
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(sourceX));
			//sourceX *= PI;

			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(sourceX));

			//TempVelocity = FVector(cosf(sourceX), 0.0f, sinf(sourceX));

			//if it hits the left side
			if (hitLoc.X < actor->GetActorLocation().X)
			{
				if (TempVelocity.X > 0)
				{
					TempVelocity.X = Velocity.X * -1.0f;
				}
			}
			//hits right side
			else if (hitLoc.X > actor->GetActorLocation().X)
			{
				if (TempVelocity.X < 0)
				{
					TempVelocity.X = Velocity.X * -1.0f;
				}
			}
			else
			{
				TempVelocity.X = 0;
			}
		}
	}

	return TempVelocity;
}

