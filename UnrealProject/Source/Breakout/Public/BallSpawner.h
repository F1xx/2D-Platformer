// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBaseActor.h"
#include "BallSpawner.generated.h"

UCLASS()
class BREAKOUT_API ABallSpawner : public AMyBaseActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallSpawner();

	/** AFallingActor class template  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABallActor> BallActorTemplate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnActor();

	UFUNCTION()
		void ShouldBeSpawned(bool spawn);


private:
	bool ShouldSpawn;
	/* arrow component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* SpawnPoint;

	/** spawn timer  */
	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		FTimerHandle SpawnTimer;

	/** timer interval to spawn new
		falling actor after previous
		actor was destroyed  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		float SpawnDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly,	BlueprintReadOnly, Category = "Config",	meta = (AllowPrivateAccess = "true"))
		int32 SpawnCount = 0;
	
};
