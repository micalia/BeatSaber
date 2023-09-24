// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BeatSaberGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API UBeatSaberGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FString patternPath;
	FString songPath;
	float bpm;

};
