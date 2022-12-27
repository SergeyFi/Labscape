// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Field/FieldSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "LaserGun.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGunFire, AActor*, Target);

UCLASS()
class LABSCAPE_API ALaserGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserGun();

	UFUNCTION(BlueprintCallable, Category = "Laser")
	void Fire();

	UPROPERTY(BlueprintAssignable, Category = "Laser")
	FGunFire OnHit;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Laser")
	bool bDebug;

	UPROPERTY(EditDefaultsOnly, Category = "Laser")
	float CooldownTime = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Laser")
	float Distance = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Laser")
	float StrainMagnitude = 5000000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Laser")
	float StrainRadius = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Laser")
	float Impulse = 1900.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Laser")
	float ImpulsePositionShift = 250.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Laser")
	TEnumAsByte<EObjectTypeQuery> ObjectTypeToTrace;

	UPROPERTY(EditDefaultsOnly, Category = "Laser")
	USoundBase* FireSound;

private:

	bool Destruction();

	void CooldownTimer();

	UFUNCTION()
	void Cooldown();

	void Effects();

	UPROPERTY()
	UFieldSystemComponent* FieldComponent;

	UPROPERTY()
	URadialFalloff* RadialFalloff;

	UPROPERTY()
	URadialVector* RadialVector;

	UPROPERTY()
	UArrowComponent* ArrowComponent;

	bool bNeedCooldown;
};
