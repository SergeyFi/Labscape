// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FallingDown/Components/Subcomponents/Subcomponent.h"
#include "UISubcomponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVisibilityDelegate, bool, Visibility);
/**
 * 
 */
UCLASS(Abstract, HideDropdown, EditInlineNew, Blueprintable)
class FALLINGDOWN_API UUISubcomponent : public USubcomponent
{
	GENERATED_BODY()

public:

	void SetVisibility(bool bVisibility);

protected:

	UPROPERTY(BlueprintAssignable)
	FVisibilityDelegate OnVisibilityChanhed;
};
