// Fill out your copyright notice in the Description page of Project Settings.


#include "SongListUI.h"
#include <UMG/Public/Components/ScrollBox.h>
#include <Kismet/KismetMathLibrary.h>
#include "Blueprint/WidgetLayoutLibrary.h"
#include <UMG/Public/Components/CanvasPanelSlot.h>
#include <Engine/DataTable.h>
#include "MusicInfoWidget.h"
#include <UMG/Public/Components/TextBlock.h>
#include <Engine/Texture2D.h>
#include <UMG/Public/Components/Image.h>
#include <Styling/SlateBrush.h>
#include <Styling/SlateColor.h>
#include <Layout/Margin.h>
#include <Math/Color.h>

USongListUI::USongListUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UDataTable> tempMusicData(TEXT("/Script/Engine.DataTable'/Game/EO/SongData.SongData'"));
	if (tempMusicData.Succeeded())
	{
		UDataTable* data = tempMusicData.Object;
		TArray<FName> rowNames = data->GetRowNames();
		for (int32 i = 0; i < rowNames.Num(); i++)
		{
			FSongDataTableRow* musicInfo = data->FindRow<FSongDataTableRow>(rowNames[i], TEXT(""));
			songData.Add(*musicInfo);
			UE_LOG(LogTemp, Warning, TEXT("musicInfo : %s"), *songData[i].songName)
		}
	}

	ConstructorHelpers::FClassFinder<UMusicInfoWidget> tempMusicInfoWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SB/Blueprints/WB_MusicInfo.WB_MusicInfo_C'"));
	if (tempMusicInfoWidget.Succeeded())
	{
		musicInfoWidgetFactory = tempMusicInfoWidget.Class;
	}
}

void USongListUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (musicInfoWidgetFactory) {
		for (int i =0; i < songData.Num(); i++)
		{
			musicInfoSlot = CreateWidget<UMusicInfoWidget>(GetWorld(), musicInfoWidgetFactory);
			
			if (musicInfoSlot) {
				musicInfoSlot->Subtitle_txt->SetText(FText::FromString(songData[i].songName));
				musicInfoSlot->artist_txt->SetText(FText::FromString(songData[i].artist));
				FString songDurationTxt = FString::Printf(TEXT("%f"), songData[i].songDuration);
				musicInfoSlot->musicTime_txt->SetText(FText::FromString(songDurationTxt));
				FString bpmtxt = FString::Printf(TEXT("%.2f"), songData[i].bpm);
				musicInfoSlot->bpm_txt->SetText(FText::FromString(bpmtxt));
				
				UTexture2D* thumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *songData[i].imagePath));
				/*FORCENOINLINE FSlateBrush(ESlateBrushDrawType::Type InDrawType, const FName InResourceName, const FMargin & InMargin, ESlateBrushTileType::Type InTiling, ESlateBrushImageType::Type InImageType, const UE::Slate::FDeprecateVector2DParameter & InImageSize, const FSlateColor & InTint, UObject * InObjectResource = nullptr, bool bInDynamicallyLoaded = false);*/
				//FSlateBrush brushThumb = 
				FSlateBrush Brush;
				/*Brush.DrawAs = ESlateBrushDrawType::Image;
				Brush.Tiling = ESlateBrushTileType::NoTile;
				Brush.Mirroring = ESlateBrushMirrorType::NoMirror;
				Brush.ImageSize = FVector2D(32.0f, 32.0f); 
				Brush.Margin = FMargin(0.0f, 0.0f, 0.0f, 0.0f); 
				Brush.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)); */

				
				Brush.SetResourceObject(thumbnail);
				musicInfoSlot->MusicThumbnail_img->SetBrush(Brush);

				SongList->AddChild(musicInfoSlot);
			}
		}

	}
}

void USongListUI::ScrollDown()
{ 
	if (SongList) {
			scrollVal += 10;
			if (scrollVal > SongList->GetScrollOffsetOfEnd()) {
				scrollVal = SongList->GetScrollOffsetOfEnd();
				return;
			}
			SongList->SetScrollOffset(scrollVal);
	}
} 

void USongListUI::ScrollUp()
{
	if (SongList) {
		scrollVal -= 10;
		if (scrollVal < 0) {
			scrollVal = 0;
			return;
		}

		SongList->SetScrollOffset(scrollVal);

	}
}
