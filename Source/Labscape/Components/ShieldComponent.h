// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Health/HealthComponent.h"
#include "ShieldComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABSCAPE_API UShieldComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShieldComponent();

	UFUNCTION(BlueprintCallable, Category = "Shield")
	void Enable();

	UFUNCTION(BlueprintCallable, Category = "Shield")
	void Disable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Shield")
	UStaticMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Shield")
	UMaterial* Material;

	UPROPERTY(EditDefaultsOnly, Category = "Shield")
	int32 ShieldCells;

private:

	UPROPERTY()
	UStaticMeshComponent* ShieldMesh;

	UPROPERTY()
	UHealthComponent* HealthComponent;

	bool bShieldEnabled;

	void CreateShieldMesh();

	UFUNCTION()
	void OnHealthSuppress(int32 Damage);
};
