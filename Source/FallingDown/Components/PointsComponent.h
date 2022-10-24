// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PointsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPointsDelegate, int32, Points);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FALLINGDOWN_API UPointsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPointsComponent();

	UFUNCTION(BlueprintCallable, Category = "Points")
	void AddPoints(int32 Count);

	UFUNCTION(BlueprintPure, Category = "Points")
	int32 GetPoints();

	UPROPERTY(BlueprintAssignable, Category = "Points")
	FPointsDelegate OnPointsUpdated;

private:

	int32 Points;

	UFUNCTION(Client, Reliable)
	void UpdatePoints(int32 Count);
		
};
