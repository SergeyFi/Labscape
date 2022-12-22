// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Labscape/Components/UI/UISubcomponent.h"
#include "UIComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABSCAPE_API UUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUIComponent();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetVisibility(bool bVisibility);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Instanced, Category = "UI")
	TArray<UUISubcomponent*> Subcomponents;

private:

	void InitSubmodules();
};
