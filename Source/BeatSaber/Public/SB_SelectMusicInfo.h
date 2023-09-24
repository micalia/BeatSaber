// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SB_SelectMusicInfo.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API USB_SelectMusicInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UImage* SelectThumb_img;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* SelectSubtitle_txt;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
		class UTextBlock* SelectArtist;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UButton* Play_btn;

		void SetSelectInfo();
};
