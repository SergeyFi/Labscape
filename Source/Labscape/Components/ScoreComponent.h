// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Labscape/Components/ReplicatedComponent.h"
#include "ScoreComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABSCAPE_API UScoreComponent : public UReplicatedComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScoreComponent();

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(float Count);

	UFUNCTION(BlueprintPure, Category = "Score")
	float GetScore();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

private:

	UPROPERTY(Replicated)
	float Score;
};
