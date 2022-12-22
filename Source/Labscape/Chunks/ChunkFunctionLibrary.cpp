// Fill out your copyright notice in the Description page of Project Settings.


#include "Labscape/Chunks/ChunkFunctionLibrary.h"

FRotator UChunkFunctionLibrary::Get90degreesRandomRotation()
{
	const TArray<float> RotationsZ {0.0f, 90.0f, 180.0f, 270.0f};

	auto RandomIndex = FMath::RandRange(0, 3);

	return {0.0f, RotationsZ[RandomIndex], 0.0f};
}
