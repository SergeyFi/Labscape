// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickable/Pickable.h"
#include "PickablePoint.generated.h"

/**
 * 
 */
UCLASS()
class LABSCAPE_API APickablePoint : public APickable
{
	GENERATED_BODY()

protected:

	virtual void OnGather(AActor* PlayerTarget) override;

	UPROPERTY(EditDefaultsOnly, Category = "Point")
	float Score = 150.0f;
};
