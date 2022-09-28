// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Chunks/ChunkFunctionLibrary.h"

FRotator UChunkFunctionLibrary::GetBlockRandomRotation()
{
	const TArray<float> RotationsZ {0.0f, 90.0f, 180.0f, 270.0f};

	auto RandomIndex = FMath::RandRange(0, 3);

	return {0.0f, RotationsZ[RandomIndex], 0.0f};
}

void UChunkFunctionLibrary::RandomRotateInstances(UInstancedStaticMeshComponent* MeshInstances)
{
	if (MeshInstances)
	{
		auto InstanceCount = MeshInstances->GetInstanceCount();

		FTransform InstanceTransform;
		
		for (auto i = 0; i < InstanceCount; ++i)
		{
			MeshInstances->GetInstanceTransform(i, InstanceTransform);

			InstanceTransform.SetRotation(GetBlockRandomRotation().Quaternion());
			
			MeshInstances->UpdateInstanceTransform(i, InstanceTransform, false, true);
		}
	}
}
