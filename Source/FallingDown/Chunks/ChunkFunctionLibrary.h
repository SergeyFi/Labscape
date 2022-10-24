// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ChunkFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGDOWN_API UChunkFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Chunk")
	static FRotator GetBlockRandomRotation();
};
