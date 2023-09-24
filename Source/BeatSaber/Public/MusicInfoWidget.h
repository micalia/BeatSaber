// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SB_SelectMusicInfo.h"
#include "MusicInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API UMusicInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	FSongInfo songSlotData;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* Subtitle_txt;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* artist_txt;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* musicTime_txt;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
		class UTextBlock* bpm_txt;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UImage* MusicThumbnail_img;

	UFUNCTION(BlueprintCallable)
	void SetSongInfo();

	UPROPERTY()
	class ALobbyGameMode* gm;
};
