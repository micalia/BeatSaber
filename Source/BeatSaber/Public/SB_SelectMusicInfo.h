// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SB_SelectMusicInfo.generated.h"

USTRUCT(BlueprintType)
struct FSongInfo
{
	GENERATED_USTRUCT_BODY()
public:
	FSongInfo():songName(""), artist(""), imagePath(""){};
	FSongInfo(FString& infoSongName, FString& infoArtist, FString& infoImagePath):songName(infoSongName), artist(infoArtist), imagePath(infoImagePath){};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString songName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString artist;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString imagePath;
};
UCLASS()
class BEATSABER_API USB_SelectMusicInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UImage* SelectThumb_img;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* SelectSubtitle_txt;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
		class UTextBlock* SelectArtist;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
		class UButton* Play_btn;

};
