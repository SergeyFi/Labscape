// Fill out your copyright notice in the Description page of Project Settings.


#include "Labscape/Actors/Gun/LaserGun.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ALaserGun::ALaserGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = FieldComponent = CreateDefaultSubobject<UFieldSystemComponent>("Field");

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("Arrow");
	ArrowComponent->SetupAttachment(RootComponent);
	
	RadialFalloff = CreateDefaultSubobject<URadialFalloff>("RadialFalloff");
	RadialVector = CreateDefaultSubobject<URadialVector>("RadialVector");
}

void ALaserGun::Fire()
{
	if (!bNeedCooldown && Destruction())
	{
		OnHit.Broadcast();
		
		if (GetNetMode() == NM_Client ||  GetNetMode() == NM_Standalone)
		{
			Effects();
		}
	}
}

bool ALaserGun::Destruction()
{
	FHitResult HitResult;

	auto DrawDebug = EDrawDebugTrace::None;

	if (bDebug)
	{
		DrawDebug = EDrawDebugTrace::ForDuration;
	}
	
	bool IsHit = 	UKismetSystemLibrary::LineTraceSingleForObjects
	(this, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * Distance,
		{ObjectTypeToTrace},false, {}, DrawDebug, HitResult, true);

	if (IsHit)
	{
		CooldownTimer();
		
		if (bDebug)
		{
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("Laser is colliding"));
		}
		
		FieldComponent->ApplyPhysicsField(true, EFieldPhysicsType::Field_ExternalClusterStrain, nullptr,
			RadialFalloff->SetRadialFalloff(StrainMagnitude, 0.0f, 1.0f, 0.0f, StrainRadius, HitResult.ImpactPoint, EFieldFalloffType::Field_Falloff_Linear));

		FieldComponent->ApplyPhysicsField(true, EFieldPhysicsType::Field_LinearVelocity, nullptr,
			RadialVector->SetRadialVector(Impulse, HitResult.ImpactPoint + GetActorForwardVector() * ImpulsePositionShift));

		return true;
	}

	return false;
}

void ALaserGun::CooldownTimer()
{
	if (CooldownTime != 0.0f)
	{
		bNeedCooldown = true;
	
		FTimerHandle Timer;
	
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ALaserGun::Cooldown, CooldownTime, false);
	}
}

void ALaserGun::Cooldown()
{
	bNeedCooldown = false;
}

void ALaserGun::Effects()
{
	if (FireSound)
	{
		UGameplayStatics::PlaySound2D(this, FireSound);
	}
}
