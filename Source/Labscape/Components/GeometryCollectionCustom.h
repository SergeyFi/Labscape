// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "GeometryCollectionCustom.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABSCAPE_API UGeometryCollectionCustom : public UGeometryCollectionComponent
{
	GENERATED_BODY()

protected:

	virtual void NotifyPhysicsCollision(const FChaosPhysicsCollisionInfo& CollisionInfo) override;

	virtual void OnCreatePhysicsState() override;

private:

	void AddPhysicsFieldsActors();
};
