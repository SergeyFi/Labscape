// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickable/Pickable.h"
#include "PickableShield.generated.h"

/**
 * 
 */
UCLASS()
class LABSCAPE_API APickableShield : public APickable
{
	GENERATED_BODY()

protected:

	virtual void OnGather(AActor* PlayerTarget) override;
};
