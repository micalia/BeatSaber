// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API AInGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AInGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	//node 블럭 스폰
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ANodeBlock> nodeBlockFactory;

	UPROPERTY(EditAnywhere)
	float spawnDelayTime = 2.5;
	float currTime;

public:
	//combo
	UPROPERTY(BlueprintReadWrite)
	int32 currCombo;
	//score
	UPROPERTY(BlueprintReadWrite)
	int32 score;

public:
	//점수 위젯
	UPROPERTY()
		class ACurrComboWidget* currComboWidgetInstance;
	UPROPERTY()
		class ASB_ScoreWidgetActor* scoreWidgetInstance;

	void ScoreUpdate();

	UPROPERTY()
		class ASB_GameResultActor* gameResultWidgetActorInstance;

	void SwitchCanvas(int32 index);

	void ShowGameResult();
	UPROPERTY()
	class USoundBase* clearSound;
public:
	UPROPERTY(EditAnywhere)
	TArray<FVector> StartNodeLoc;

	UPROPERTY()
	class AVR_Player* player;

	UPROPERTY(BlueprintReadWrite)
	bool bGameStart;

	UPROPERTY()
	class UBeatSaberGameInstance* gi;

	UFUNCTION(BlueprintCallable)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void BlendCam();

	UPROPERTY()
		class AEO_Sync* sync;

	void SetMusicInfoToResultPanel(FString songName, FString artist, FString thumbPath);

	UFUNCTION(BlueprintImplementableEvent)
	void HideUI();
public:
	bool bGameEnd;

	void EndGame();
	UPROPERTY(EditAnywhere)
	int32 rankScoregap = 150;
	UPROPERTY(EditAnywhere)
	int32 noteScore = 10;
	FString CalculateScore(int32 score);

public:
	int32 currentRankVal;
	
	UFUNCTION(BlueprintCallable)
	void MinusScoreFromFullScore();

	FNumberFormattingOptions numberformat;
};
