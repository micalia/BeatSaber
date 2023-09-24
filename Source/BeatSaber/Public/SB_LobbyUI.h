// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SB_LobbyUI.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API USB_LobbyUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		class USB_SelectMusicInfo* WB_SelectMusicInfo;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		class USongListUI* WB_SongListUI;
};
