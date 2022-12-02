// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/UI/UISubcomponent.h"

void UUISubcomponent::SetVisibility(bool bVisibility)
{
	OnVisibilityChanhed.Broadcast(bVisibility);
}
