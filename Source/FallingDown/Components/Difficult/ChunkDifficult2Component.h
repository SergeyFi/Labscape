// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DifficultComponent.h"
#include "ChunkDifficult2Component.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class FALLINGDOWN_API UChunkDifficult2Component : public UDifficultComponent
{
	GENERATED_BODY()

public:

	UChunkDifficult2Component();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void ApplyDifficult() override;

	UPROPERTY(EditAnywhere)
	float MaxRotationSpeed = 300.0f;

	UPROPERTY(EditAnywhere)
	float MinRotationSpeed = 100.0f;

private:

	float RotationSpeed;
};
