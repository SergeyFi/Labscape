// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FallingMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FALLINGDOWN_API UFallingMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFallingMovementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Input", Server, Unreliable)
	void AddMovementInput(FVector Input);

	UFUNCTION(BlueprintPure, Category = "Input")
	float GetFallingSpeed();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float MaxFallingSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float FallingVelocity;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float MovementSpeed = 900.0f;

	FVector InputLast;

	UPrimitiveComponent* RootComponent;

private:
	
	void Falling();

	void Movement();
};


