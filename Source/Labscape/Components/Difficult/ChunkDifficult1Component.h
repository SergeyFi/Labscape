// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DifficultComponent.h"
#include "ChunkDifficult1Component.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class LABSCAPE_API UChunkDifficult1Component : public UDifficultComponent
{
	GENERATED_BODY()

public:

	UChunkDifficult1Component();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void ApplyDifficult() override;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 400.0f;

	UPROPERTY(EditAnywhere)
	float MinRotation = -180.0f;

	UPROPERTY(EditAnywhere)
	float MaxRotation = 180.0f;

	UFUNCTION(Client, Reliable)
	void SetMaxZRotationOnClient(float Rotation);

private:

	float CurrentZRotation;
	float MaxZRotation;
};
