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
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

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
	class UTextBlock* text_Tip;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* scroll_SongList;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Back;
	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Add;
	/*UPROPERTY(meta = (BindWidget))
	class UButton* btn_Delete;*/
	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Play;
	UPROPERTY(meta = (BindWidget))
	class UButton* btn_RedNote;
	UPROPERTY(meta = (BindWidget))
	class UButton* btn_BlueNote;
	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Bomb;
	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Wall;

private:
	UPROPERTY(VisibleAnywhere, Category="Settings|Generate")
	TSubclassOf<class UEO_EditorSongSlot> songSlot;
	UPROPERTY(VisibleAnywhere, Category="Settings|DataTable")
	class UDataTable* songDatatable;

	UPROPERTY(VisibleAnywhere, Category="Settings|Generate")
	TSubclassOf<class AEO_GridController> gridControllerFactory;
	UPROPERTY(VisibleAnywhere)
	class AEO_GridController* gridController;

public:
	FString selectSongPath = "none";
	FString redBlockInfo = TEXT("빨간 화살표 노트:\n왼손의 붉은 세이버로 해당 화살표의 방향으로 베어내야 하는 노트\n\n빨간 점 노트:\n방향이 없는 노트\n\n(Q키로 타입 변환)");
	FString blueBlockInfo = TEXT("파란 화살표 노트:\n오른손의 파란 세이버로 해당 화살표의 방향으로 베어내야 하는 노트\n\n파란 점 노트:\n방향이 없는 노트\n\n(Q키로 타입 변환)");
	FString bombInfo = TEXT("폭탄:\n베어내면 체력이 닳는 장애물");
	FString wallInfo = TEXT("벽:\n머리(HMD)에 닿으면 체력이 닳는 장애물\n\n(시작점과 끝점을 지정해야 한다.)");

	float selectBPM;
	float selectOffset;

private:
	void GenerateList();
	UFUNCTION()
	void AddPattern();
	UFUNCTION()
	void SoundPlay();
	UFUNCTION()
	void ChangeRedNote();
	UFUNCTION()
	void ChangeBlueNote();
	UFUNCTION()
	void ChangeBomb();
	UFUNCTION()
	void ChangeWall();

public:
	void SaveSelectedData(FString songPath, float BPM, float offset);
};
