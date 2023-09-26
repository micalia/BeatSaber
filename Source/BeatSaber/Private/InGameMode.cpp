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

	player->rightSword->SetVisibility(true);
	player->leftSword->SetVisibility(true);
	player->rightRemoteController->SetVisibility(false);

	gi = Cast<UBeatSaberGameInstance>(GetGameInstance());
	if (gi) {
		UE_LOG(LogTemp, Warning, TEXT("SongPath : %s / PatternPath : %s / bpm : %f"), *gi->songPath, *gi->patternPath, gi->bpm)

	}

	for (TActorIterator<AEO_Sync> it(GetWorld()); it; ++it)
	{
		sync = *it;
	}
}

void AInGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (bGameStart) {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("gameStart : true")), true, FVector2D(1, 1));
		UE_LOG(LogTemp, Warning, TEXT("gameStart : true"))
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("gameStart : false")), true, FVector2D(1, 1));
		UE_LOG(LogTemp, Warning, TEXT("gameStart : false"))
	}*/

	//currTime+= DeltaTime;

	//if (currTime > spawnDelayTime) { 
	//	currTime = 0;

	//////임시 생성위치
	//	FVector testSpawnPos = FVector(1300,0,0);
	//
	//	float randomRotateVal = UKismetMathLibrary::RandomFloatInRange(0,360);

	//	//GetWorld()->SpawnActor<ANodeBlock>(nodeBlockFactory, testSpawnPos, FRotator(0));

	//}

	ScoreUpdate();
}

void AInGameMode::ScoreUpdate()
{	
	if (currComboWidgetInstance) {
		currComboWidgetInstance->comboWidgetInstance->currCombo_txt->SetText(FText::AsNumber(currCombo));
	}
	
	if (scoreWidgetInstance) {
		if (scoreWidgetInstance->scoreWidgetInstance) {
			scoreWidgetInstance->scoreWidgetInstance->currScoreUI_txt->SetText(FText::AsNumber(score));
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
