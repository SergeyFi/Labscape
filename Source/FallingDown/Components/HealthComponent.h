// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthEvent, int32, Health);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FALLINGDOWN_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintPure, Category = "Health")
	int32 GetHealth() const;
	
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthEvent OnHealtCountChanged;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 Health;
};
