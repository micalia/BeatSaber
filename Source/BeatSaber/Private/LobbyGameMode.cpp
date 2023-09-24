// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include <UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include "SB_SelectMusicInfo.h"
#include "EngineUtils.h"
#include "SB_LobbyUiActor.h"
#include "SB_LobbyUI.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <UMG/Public/Components/TextBlock.h>
#include <UMG/Public/Components/Image.h>
#include <Sound/SoundBase.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundCue.h>
#include <Components/AudioComponent.h>

ALobbyGameMode::ALobbyGameMode()
{
	static ConstructorHelpers::FObjectFinder<USoundCue> tempPreviewSoundCue(TEXT("/Script/Engine.SoundCue'/Game/SB/Sounds/LobbyPreviewSound.LobbyPreviewSound'"));
	if (tempPreviewSoundCue.Succeeded()) {
		SoundCue = tempPreviewSoundCue.Object;
	}
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ASB_LobbyUiActor> it(GetWorld()); it; ++it)
	{
		lobbyUiActor = *it;
	}
	
	if (lobbyUiActor) {
		lobbyUIinstance = Cast<USB_LobbyUI>(lobbyUiActor->compWidget->GetWidget());
	}
}

void ALobbyGameMode::SetSelectMusicInfo(FString songName, FString artist, FString thumbPath)
{
	if (lobbyUIinstance) {
		lobbyUIinstance->WB_SelectMusicInfo->SelectSubtitle_txt->SetText(FText::FromString(songName));
		lobbyUIinstance->WB_SelectMusicInfo->SelectArtist->SetText(FText::FromString(artist));

		UTexture2D* thumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *thumbPath));
		FSlateBrush Brush;
		Brush.DrawAs = ESlateBrushDrawType::Image;
		Brush.Tiling = ESlateBrushTileType::NoTile;
		Brush.Mirroring = ESlateBrushMirrorType::NoMirror;
		Brush.ImageSize = FVector2D(32.0f, 32.0f);
		Brush.Margin = FMargin(0.0f, 0.0f, 0.0f, 0.0f);
		Brush.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		
		Brush.SetResourceObject(thumbnail);
		lobbyUIinstance->WB_SelectMusicInfo->SelectThumb_img->SetBrush(Brush);

	}
}

void ALobbyGameMode::PreviewSoundPlay(FString songPath, float previewSongTime)
{
	FStreamableManager assetLoader;
	USoundBase* musicTexture = Cast<USoundBase>(assetLoader.LoadSynchronous(FPaths::ConvertRelativePathToFull(songPath)));
	if (musicTexture) { 
		if (lobbyUiActor) {
			lobbyUiActor->audioComp->SetSound(musicTexture);
			lobbyUiActor->audioComp->Play(previewSongTime);
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("previewSongTime : %f"), previewSongTime), true, FVector2D(4,4));
		}
	}
	
}
