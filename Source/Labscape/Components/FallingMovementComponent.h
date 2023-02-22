// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FallingMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABSCAPE_API UFallingMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFallingMovementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void AddMovementInput(FVector Input, float Scale);

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

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float MovementDamping = 300.0f;

	FVector InputSum;

	UPrimitiveComponent* RootComponent;

	UFUNCTION(BlueprintCallable, Server, Unreliable)
	void SendMovementInputToServer(FVector Input, float Scale);

private:
	
	void Falling();

	void Movement();

	void Damping();

	void SpeedLimit();

	FVector ScaleInput(FVector Input, float Scale);
};


