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

public:
	//점수 위젯
	UPROPERTY()
	class ACurrComboWidget* currComboWidgetInstance;

	void ScoreUpdate();
public:
	UPROPERTY(EditAnywhere)
	TArray<FVector> StartNodeLoc;

	UPROPERTY()
	class AVR_Player* player;

	UPROPERTY(BlueprintReadWrite)
	bool bGameStart;
};
