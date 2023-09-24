#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EO_EditorWidget.generated.h"

UCLASS()
class BEATSABER_API UEO_EditorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UEO_EditorWidget(const FObjectInitializer& Object);

private:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* ws_Switcher;

	UPROPERTY(meta = (BindWidget))
	class UImage* image_SongImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* text_Title;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* text_Artist;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* text_BPM;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* text_SongDuration;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* scroll_SongList;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Back;
	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Add;
	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Delete;

private:
	UPROPERTY(VisibleAnywhere, Category="Settings|Generate")
	TSubclassOf<class UEO_EditorSongSlot> songSlot;
	UPROPERTY(VisibleAnywhere, Category="Settings|DataTable")
	class UDataTable* songDatatable;

	UPROPERTY(VisibleAnywhere, Category="Settings|Generate")
	TSubclassOf<class AEO_GridController> gridControllerFactory;

public:
	FString selectSongPath;

	float selectBPM;
	float selectOffset;

private:
	void GenerateList();
	UFUNCTION()
	void AddPattern();

public:
	void SaveSelectedData(FString songPath, float BPM, float offset);
};
