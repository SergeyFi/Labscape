// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "ReplicatedComponent.generated.h"


UCLASS( ClassGroup=(Custom), Abstract, HideDropdown )
class FALLINGDOWN_API UReplicatedComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UReplicatedComponent();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	
	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}
};
