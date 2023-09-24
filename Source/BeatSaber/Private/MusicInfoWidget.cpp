// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicInfoWidget.h"
#include "SongListUI.h"
#include <UMG/Public/Components/PanelWidget.h>
#include "LobbyGameMode.h"

void UMusicInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gm = Cast<ALobbyGameMode>(GetWorld()->GetAuthGameMode());
}

void UMusicInfoWidget::SetSongInfo()
{ 
	gm->SetSelectMusicInfo(songSlotData.songName, songSlotData.artist, songSlotData.imagePath);
	gm->PreviewSoundPlay(songSlotData.songPath, songSlotData.previewSongDuration);
}
