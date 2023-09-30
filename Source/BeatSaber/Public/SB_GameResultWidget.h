// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SB_GameResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API USB_GameResultWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	class UWidgetSwitcher* SwitchWidget;
};
