// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DifficultComponent.generated.h"


UCLASS( ClassGroup=(Custom), Abstract )
class LABSCAPE_API UDifficultComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDifficultComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Difficult")
	bool Enabled = true;

	UPROPERTY(EditDefaultsOnly, Category = "Difficult")
	float StartTime;

	UPROPERTY(EditDefaultsOnly, Category = "Difficult")
	float EndTime;

	virtual void ApplyDifficult();
		
};
