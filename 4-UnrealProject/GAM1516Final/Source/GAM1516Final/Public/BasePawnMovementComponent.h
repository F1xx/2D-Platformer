// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "BasePawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAM1516FINAL_API UBasePawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
		UBasePawnMovementComponent();

		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		virtual void MoveRight(float value, float speed);
		virtual void Jump();
		virtual void HandleJump(float DeltaTime);
		virtual void StopJump();

		void SetOnFloor(bool value) { m_OnFloor = value; }
		void SetCanJump(bool value) { m_CanJump = value; }

        bool GetOnFloor() { return m_OnFloor;  }

		void SetOwner(class ABasePawn* owner) { m_Owner = owner; }

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		FTimerHandle JumpTimer;

	//UPROPERTY(EditAnywhere, Category = "Config")
		//float RunSpeed = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Config")
		float JumpHeight = 500.0f;
	UPROPERTY(EditAnywhere, Category = "Config")
		float MaxJumpTime = 0.2f;

	FVector currVelocity;

	float m_Direction = 1.0f;

	bool m_CanJump = true;
	bool m_IsJumping = false;
	bool m_OnFloor = false;

	float m_Jumptime = MaxJumpTime;

private:
	class ABasePawn* m_Owner;
};
