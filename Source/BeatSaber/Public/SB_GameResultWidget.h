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
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* SwitchWidget;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UTextBlock* Subtitle_txt;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UTextBlock* artist_txt;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UImage* MusicThumbnail_img;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UTextBlock* Score_txt;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UTextBlock* Rank_txt;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UTextBlock* Subtitle_txt2;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UTextBlock* artist_txt2;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UImage* MusicThumbnail_img2;

	UFUNCTION(BlueprintImplementableEvent)
	void FadeEffect();
};
