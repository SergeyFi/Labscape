// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "Components/FallingMovementComponent.h"
#include "NiagaraComponent.h"
#include "BoostComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABSCAPE_API UBoostComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBoostComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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

	UPROPERTY(EditDefaultsOnly, Category = "Boost")
	float FOVAdjust = 30.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Boost")
	float FOVIncreaseSpeed = 18.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Boost|FX")
	UNiagaraSystem* NiagaraSystem;

	UPROPERTY(EditDefaultsOnly, Category = "Boost|FX")
	FVector FXOffset = {0.0f, 0.0f , 100.0f};
	

private:

	UPROPERTY()
	UFallingMovementComponent* FallingMovement;

	UCameraComponent* Camera;

	float CurrentFov = 0.0f;

	bool bBoost;

	UPROPERTY()
	UNiagaraComponent* NiagaraComponent;

	void FOVBoost(float DeltaTime);
	
	void InitFX();
};
