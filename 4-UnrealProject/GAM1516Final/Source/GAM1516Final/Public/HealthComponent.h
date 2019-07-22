// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAM1516FINAL_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHealthComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    float TakeDamage(float adamage);

    float currentHealth;
    float maxHealth;


  
	void SetCurrentHealth(float health) { currentHealth = health; }
	float GetCurrentHealth() { return currentHealth; }

   

	void SetMaxHealth(float health) { maxHealth = health; }
	float GetMaxHealth() { return maxHealth; }
};
