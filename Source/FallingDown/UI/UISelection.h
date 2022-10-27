// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UISelection.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSelectionEvent);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Placeable)
class FALLINGDOWN_API UUISelection : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection")
	UUISelection* Up;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection")
	UUISelection* Down;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection")
	UUISelection* Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection")
	UUISelection* Right;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Selection")
	FSelectionEvent OnSelectEvent;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Selection")
	FSelectionEvent OnUnselectEvent;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Selection")
	FSelectionEvent OnActivatedEvent;
};
