// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Engine/DataTable.h>
#include "EO_SongDataTable.h"
#include "SongListUI.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API USongListUI : public UUserWidget
{
	GENERATED_BODY()

public:	
	USongListUI(const FObjectInitializer &ObjectInitializer);

	UPROPERTY()
		TArray<FSongDataTableRow> songData;

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class UMusicInfoWidget> musicInfoWidgetFactory;

	UPROPERTY()
	class UMusicInfoWidget* musicInfoSlot;

	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	class UScrollBox* SongList;

	UPROPERTY(BlueprintReadOnly)
	float scrollVal;

	UFUNCTION(BlueprintCallable)
	void ScrollUp();
	UFUNCTION(BlueprintCallable)
	void ScrollDown();
};
