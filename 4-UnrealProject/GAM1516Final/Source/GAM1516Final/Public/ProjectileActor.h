// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "ProjectileActor.generated.h"

//Enum of the different types of bullets
UENUM(BlueprintType)
enum BulletType
{
	BulletType_Standard,
	BulletType_Fast,
	BulletType_Slow,
	BulletType_Bouncy,
	BulletType_Piercing,
};

/**
 * 
 */
UCLASS()
class GAM1516FINAL_API AProjectileActor : public ABaseActor
{
	GENERATED_BODY()
	
public:

	AProjectileActor();
	//create a more specific
	AProjectileActor(float lifelength, BulletType type);

	virtual void Tick(float DeltaTime) override;

	//set a class of bullettype which will set the stats for the bullet.
	void SetBulletType(TEnumAsByte<BulletType> type);

	UFUNCTION(BlueprintCallable, Category = "Hit Detection")
		virtual void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit);
	
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when something leaves the sphere component */
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	/** life timer  */
	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		FTimerHandle DeathTimer;

	UPROPERTY(EditAnywhere, Category = "Collision Sphere")
		class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, Category = "Projectile Movement")
		class UBulletMovementComponent* Projectile;

	//Amount of time the projectile will live in the world in seconds
	float Lifelength;
	TEnumAsByte<BulletType> bulletType;

	void Die();
	void ConstructComponents();
	void ResetBullet();
	
protected:
    //called when the game starts or when spawned
    virtual void BeginPlay() override;

	UFUNCTION()
	virtual void HandleCollision(class UPrimitiveComponent* hitcomp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, const FHitResult & Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* ProjectileFX;

	class UPaperSprite* Sprites[4];
};
