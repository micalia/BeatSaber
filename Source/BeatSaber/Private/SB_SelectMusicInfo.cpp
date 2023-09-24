// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_SelectMusicInfo.h"
#include "LobbyGameMode.h"
#include "EO_SongDataTable.h"
#include "SB_LobbyUI.h"
#include "SongListUI.h"
#include <UMG/Public/Components/TextBlock.h>
#include <UMG/Public/Components/Image.h>

void USB_SelectMusicInfo::NativeConstruct()
{
	Super::NativeConstruct();

	ALobbyGameMode* gm = Cast<ALobbyGameMode>(GetWorld()->GetAuthGameMode());
	
	FSongDataTableRow* row = gm->lobbyUIinstance->WB_SongListUI->listDataTable->FindRow<FSongDataTableRow>(FName(*(FString::FormatAsNumber(0))), FString(""));
	
	gm->lobbyUIinstance->WB_SelectMusicInfo->SelectSubtitle_txt->SetText(FText::FromString(row->songName));
	gm->lobbyUIinstance->WB_SelectMusicInfo->SelectArtist->SetText(FText::FromString(row->artist));

	UTexture2D* thumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *row->imagePath));
	FSlateBrush Brush;
	Brush.DrawAs = ESlateBrushDrawType::Image;
	Brush.Tiling = ESlateBrushTileType::NoTile;
	Brush.Mirroring = ESlateBrushMirrorType::NoMirror;
	Brush.ImageSize = FVector2D(32.0f, 32.0f);
	Brush.Margin = FMargin(0.0f, 0.0f, 0.0f, 0.0f);
	Brush.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

	Brush.SetResourceObject(thumbnail);
	gm->lobbyUIinstance->WB_SelectMusicInfo->SelectThumb_img->SetBrush(Brush);
}
