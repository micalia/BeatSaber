// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SB_HpUiWidget.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API USB_HpUiWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HpBar;
};
