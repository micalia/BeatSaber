// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMode.h"
#include "NodeBlock.h"
#include <Kismet/KismetMathLibrary.h>

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
}

void AInGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currTime+= DeltaTime;

	if (currTime > spawnDelayTime) {
		currTime = 0;

	////임시 생성위치
		FVector testSpawnPos = FVector(1300,0,0);
	
		float randomRotateVal = UKismetMathLibrary::RandomFloatInRange(0,360);

		GetWorld()->SpawnActor<ANodeBlock>(nodeBlockFactory, testSpawnPos, FRotator(0));

	}
}
