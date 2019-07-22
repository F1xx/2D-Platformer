// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "BasePawn.h"
#include "PlayerPawn.h"


UBasePawnMovementComponent::UBasePawnMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	currVelocity = FVector(0.0f, 0.0f, 0.0f);
}

void UBasePawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	if (!m_OnFloor)
	{
		m_Jumptime -= DeltaTime;
		if (m_Jumptime <= 0.0f)
		{
			StopJump();
		}
	}

	if (m_IsJumping)
	{
		HandleJump(DeltaTime);
	}
}

void UBasePawnMovementComponent::MoveRight(float value, float speed)
{
	if (m_Owner)
	{
		FVector currVelocity = m_Owner->Capsule->BodyInstance.GetUnrealWorldVelocity();
		if (value != 0)
		{
			FVector newVelocity = FVector(speed * value, 0.0f, currVelocity.Z);
			FVector airVelocity(1.0f, 0.0f, 0.0f);
			airVelocity *= FVector(15 * speed) * value;
            
			if (m_OnFloor)
			{
				m_Owner->Capsule->BodyInstance.SetLinearVelocity(newVelocity, false);
                
			}
			else
			{
				if ((currVelocity.X > newVelocity.X && value < 0) || (currVelocity.X < newVelocity.X && value > 0))
				{
					m_Owner->Capsule->BodyInstance.AddForce(airVelocity);
                    
				}
			}

			if (currVelocity.X > 40.0f)
			{
				m_Direction = 1.0f;
				m_Owner->Sprite->SetRelativeRotation(FRotator(FRotator::ZeroRotator));
			}
			else if (currVelocity.X < -40.0f)
			{
				m_Direction = -1.0f;
				m_Owner->Sprite->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
			}
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Yellow, "No Owner " + PawnOwner->GetName());
	}
}

void UBasePawnMovementComponent::Jump()
{
	if (m_Owner)
	{
		if (m_CanJump)
		{
			m_OnFloor = false;
			m_IsJumping = true;
		}
	}
}

void UBasePawnMovementComponent::HandleJump(float DeltaTime)
{
	if (m_Owner)
	{
 		FVector FinalVel = FVector(0.0f, 0.0f, DeltaTime * JumpHeight);
 		m_Owner->Capsule->BodyInstance.AddImpulse(FinalVel, true);	
	}
}

void UBasePawnMovementComponent::StopJump()
{
	if (m_Owner)
	{
		m_CanJump = false;
		m_IsJumping = false;
		m_Jumptime = MaxJumpTime;
	}
}

void UBasePawnMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

