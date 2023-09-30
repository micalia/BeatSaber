// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicInfoWidget.h"
#include "SongListUI.h"
#include <UMG/Public/Components/PanelWidget.h>
#include "LobbyGameMode.h"
#include "BeatSaberGameInstance.h"

void UMusicInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gm = Cast<ALobbyGameMode>(GetWorld()->GetAuthGameMode());
}

void UMusicInfoWidget::SetSongInfo()
{ 
	if (gm)
	{ 
		gm->SetSelectMusicInfo(songSlotData.songName, songSlotData.artist, songSlotData.imagePath);
		gm->PreviewSoundPlay(songSlotData.songPath, songSlotData.previewSongDuration);
		if (gm->gi) {
			gm->gi->songName = songSlotData.songName;
			gm->gi->artist = songSlotData.artist;
			gm->gi->imagePath = songSlotData.imagePath;
			gm->gi->songPath = songSlotData.songPath;
			gm->gi->patternPath = songSlotData.patternPath;
			gm->gi->bpm = songSlotData.bpm;
		}
	}
}
