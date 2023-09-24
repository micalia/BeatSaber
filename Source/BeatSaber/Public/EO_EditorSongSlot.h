#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EO_EditorSongSlot.generated.h"

UCLASS()
class BEATSABER_API UEO_EditorSongSlot : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* text_Title;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* text_Artist;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* text_BPM;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Slot;

	FString imagePath;
	FString songPath;

	float bpm = 0;
	float songDuration = 0;
	

private:
	UFUNCTION()
	void SongSelectButtonClick();
	UFUNCTION()
	class UEO_EditorWidget* ReturnParentWidget();
};
