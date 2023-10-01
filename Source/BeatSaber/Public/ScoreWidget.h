// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* currScoreUI_txt;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* currentRank_txt;
};
