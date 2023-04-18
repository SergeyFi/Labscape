// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Statistic/Classes/StatGamesPlayed.h"

UStatGamesPlayed::UStatGamesPlayed()
{
	Name = FText::FromString("Game number");
}

FString UStatGamesPlayed::GetStringValue_Virtual()
{
	return FString::FromInt(GamesPlayed);
}
