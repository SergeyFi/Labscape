// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Subcomponent.generated.h"

/**
 * 
 */
UCLASS(Abstract, HideDropdown, EditInlineNew, Blueprintable)
class FALLINGDOWN_API USubcomponent : public UObject
{
	GENERATED_BODY()

public:
	
	virtual void Init(APawn* NewPlayer);

	virtual UWorld* GetWorld() const override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnInit(APawn* Player);

	APawn* PlayerPawn;
};
