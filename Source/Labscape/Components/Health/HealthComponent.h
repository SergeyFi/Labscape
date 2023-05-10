// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthSubcomponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDamageEvent, int32, Damage);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABSCAPE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddDamage(int32 Damage);

	UFUNCTION(BlueprintPure, Category = "Health")
	int32 GetHealth() const;

	UFUNCTION(BlueprintPure, Category = "Health")
	bool HealthIsOver();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Kill();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SuppressDamage(bool bSuppress);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(int32 Count);
	
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthDamageEvent OnDamage;
	
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthDamageEvent OnDamageSuppress;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthEvent OnHealthEnd;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthEvent OnHealthChanged;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 Health;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 HealthMax;

	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Health")
	TArray<UHealthSubcomponent*> Subcomponents;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	bool bGodMode;

private:

	bool bSuppressDamage;
};
