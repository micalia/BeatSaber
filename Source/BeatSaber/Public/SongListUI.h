// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SongListUI.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API USongListUI : public UUserWidget
{
	GENERATED_BODY()

public:	
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	class UScrollBox* SongList;

	UPROPERTY(BlueprintReadOnly)
	float scrollVal;

	UFUNCTION(BlueprintCallable)
	void ScrollUp();
	UFUNCTION(BlueprintCallable)
	void ScrollDown();
};
