// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMode.h"
#include "NodeBlock.h"
#include <Kismet/KismetMathLibrary.h>
#include "ComboWidget.h"
#include <Kismet/GameplayStatics.h>
#include "CurrComboWidget.h"
#include <UMG/Public/Components/TextBlock.h>
#include "VR_Player.h"
#include "BeatSaberGameInstance.h"
#include "EngineUtils.h"
#include "EO_Sync.h"
#include "SB_ScoreWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "ScoreWidget.h"
#include "SB_GameResultActor.h"
#include "SB_GameResultWidget.h"
#include <UMG/Public/Components/WidgetSwitcher.h>
#include <UMG/Public/Components/Image.h>

AInGameMode::AInGameMode() {
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<ANodeBlock> tempNodeBlockObj(TEXT("/Script/Engine.Blueprint'/Game/SB/Blueprints/BP_NodeBlock.BP_NodeBlock_C'"));
	if (tempNodeBlockObj.Succeeded()) {
		nodeBlockFactory = tempNodeBlockObj.Class;
	}
}

void AInGameMode::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	currComboWidgetInstance = Cast<ACurrComboWidget>(UGameplayStatics::GetActorOfClass(GetWorld(), ACurrComboWidget::StaticClass()));
	scoreWidgetInstance = Cast<ASB_ScoreWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ASB_ScoreWidgetActor::StaticClass()));
	gameResultWidgetActorInstance = Cast<ASB_GameResultActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ASB_GameResultActor::StaticClass()));

	player->rightSword->SetVisibility(true);
	player->leftSword->SetVisibility(true);
	player->rightRemoteController->SetVisibility(false);

	gi = Cast<UBeatSaberGameInstance>(GetGameInstance());
	if (gi) {
		UE_LOG(LogTemp, Warning, TEXT("SongPath : %s / PatternPath : %s / bpm : %f"), *gi->songPath, *gi->patternPath, gi->bpm)
		SetMusicInfoToResultPanel(gi->songName, gi->artist, gi->imagePath);

	}

	for (TActorIterator<AEO_Sync> it(GetWorld()); it; ++it)
	{
		sync = *it;
	}

	numberformat.UseGrouping = false;
}

void AInGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ScoreUpdate();

	if (!bGameEnd) {
		if(bGameEnd == true) return;
		if (player->currHp <= 0) {
			bGameEnd = true;
			player->rightSword->SetVisibility(false);
			player->leftSword->SetVisibility(false);
			player->rightRemoteController->SetVisibility(true);
			HideUI();
			ShowGameResult();
		}
	}
}

void AInGameMode::ScoreUpdate()
{	
	if (currComboWidgetInstance) {
		currComboWidgetInstance->comboWidgetInstance->currCombo_txt->SetText(FText::AsNumber(currCombo, &numberformat));
	}
	
	if (scoreWidgetInstance) {
		if (scoreWidgetInstance->scoreWidgetInstance) {
			scoreWidgetInstance->scoreWidgetInstance->currScoreUI_txt->SetText(FText::AsNumber(score, &numberformat));
		}
	}
}

void AInGameMode::SwitchCanvas(int32 index)
{ 
	gameResultWidgetActorInstance->gameResultWidgetInstance->SwitchWidget->SetActiveWidgetIndex(index);
}

void AInGameMode::ShowGameResult()
{ 
	if (player) {
		if (player->currHp <= 0) {
			gameResultWidgetActorInstance->gameResultWidgetInstance->SetRenderOpacity(1);
			SwitchCanvas(1);
		}
		else {
			gameResultWidgetActorInstance->gameResultWidgetInstance->SetRenderOpacity(1);
			SwitchCanvas(0);
		}
	}
}

void AInGameMode::GameStart()
{
	if (sync) {
		sync->GenerateNote(gi->songPath, gi->patternPath, gi->bpm);
		sync->GameStart();
	}
}

void AInGameMode::SetMusicInfoToResultPanel(FString songName, FString artist, FString thumbPath)
{
	if (gameResultWidgetActorInstance) {
		//ClearCanvas
		gameResultWidgetActorInstance->gameResultWidgetInstance->Subtitle_txt->SetText(FText::FromString(songName));
		gameResultWidgetActorInstance->gameResultWidgetInstance->artist_txt->SetText(FText::FromString(artist));

		UTexture2D* thumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *thumbPath));
		FSlateBrush Brush;
		Brush.DrawAs = ESlateBrushDrawType::Image;
		Brush.Tiling = ESlateBrushTileType::NoTile;
		Brush.Mirroring = ESlateBrushMirrorType::NoMirror;
		Brush.ImageSize = FVector2D(32.0f, 32.0f);
		Brush.Margin = FMargin(0.0f, 0.0f, 0.0f, 0.0f);
		Brush.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		
		Brush.SetResourceObject(thumbnail);
		gameResultWidgetActorInstance->gameResultWidgetInstance->MusicThumbnail_img->SetBrush(Brush);

		//FailCanvas
		gameResultWidgetActorInstance->gameResultWidgetInstance->Subtitle_txt2->SetText(FText::FromString(songName));
		gameResultWidgetActorInstance->gameResultWidgetInstance->artist_txt2->SetText(FText::FromString(artist));
		gameResultWidgetActorInstance->gameResultWidgetInstance->MusicThumbnail_img2->SetBrush(Brush);

	}
}
