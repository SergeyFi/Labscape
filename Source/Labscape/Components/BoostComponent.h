// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/FallingMovementComponent.h"
#include "BoostComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABSCAPE_API UBoostComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBoostComponent();

	UFUNCTION(BlueprintCallable, Category = "Boost")
	void Boost();

	UFUNCTION(BlueprintCallable, Category = "Boost")
	void BoostStop();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Boost")
	float VelocityScalerMod = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Boost")
	float MaxSpeedMod = 3000.0f;

private:

	UPROPERTY()
	UFallingMovementComponent* FallingMovement;
};
