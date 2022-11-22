// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chunk.generated.h"


UCLASS(Abstract)
class FALLINGDOWN_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();

	UFUNCTION(BlueprintPure, Category = "Chunk")
	FVector GetChunkSize() const;
	
	UFUNCTION(BlueprintPure, Category = "Chunk")
	const TArray<TSubclassOf<AChunk>>& GetNextChunks();
	
protected:

	UPROPERTY(EditDefaultsOnly)
	FVector ChunkSize;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AChunk>> NextChunksClasses;
};
