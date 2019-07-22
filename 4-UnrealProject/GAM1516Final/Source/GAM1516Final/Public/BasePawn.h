// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ProjectileActor.h"
#include "BasePawn.generated.h"

UENUM(BlueprintType)
enum class EAnimState : uint8
{
	Idle,
	Jumping,
	Walking,
	StartShooting,
	Shooting,
	Dying,
	Dead,
	Hit
};

UCLASS()
class GAM1516FINAL_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<BulletType> bulletType;

	void UpdateAnimation();

	class AMyGameStateBase* m_GameState;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    float RunSpeed;

	virtual void Shoot();
	virtual void StopShoot();

	virtual void HurtPlayer();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(Category = Character, VisibleAnyWhere, meta = (AllowPrivateAccess))
		class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, Category = "Visual")
		class UPaperFlipbookComponent* Sprite;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Visual", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* WalkFlipbook;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Visual", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* JumpFlipbook;

    UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Visual", meta = (AllowPrivateAccess = "true"))
        class UPaperFlipbook* StartJumpFlipbook;

    UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Visual", meta = (AllowPrivateAccess = "true"))
        class UPaperFlipbook* MidJumpFlipbook;

    UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Visual", meta = (AllowPrivateAccess = "true"))
        class UPaperFlipbook* EndJumpFlipbook;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Visual", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* StartShootFlipbook;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Visual", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* ShootFlipbook;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Visual", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* IdleFlipbook;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Visual", meta = (AllowPrivateAccess = "true"))
		EAnimState AnimState = EAnimState::Idle;

	UPROPERTY(EditAnywhere, Category = "Config")
		class UBasePawnMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, Category = "Config")
		class UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AProjectileActor> ProjectileTemplate;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Hit Detection")
		void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	UFUNCTION()
		virtual void Disable();

	UFUNCTION()
		virtual void Enable();

	UFUNCTION(BlueprintCallable, Category = "AAA")
		void SetState(EAnimState newstate);

	TEnumAsByte<BulletType> GetBulletType() { return bulletType; }
	void SetBulletType(TEnumAsByte<BulletType> type) { bulletType = type; }

	virtual void Die();

	void MoveRight(float value);
	void Jump();
	void StopJump();
	void Land();

	AMyGameStateBase* GetGameState() { return m_GameState; }

private:

};
