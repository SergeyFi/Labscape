// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UISubcomponent.generated.h"

/**
 * 
 */
UCLASS(Abstract, HideDropdown, EditInlineNew, Blueprintable)
class FALLINGDOWN_API UUISubcomponent : public UObject
{
	GENERATED_BODY()

public:
	
	virtual void Init(APlayerController* NewPlayer);

	virtual UWorld* GetWorld() const override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnInit(APlayerController* Player);

private:

	APlayerController* PlayerOwner;
};
