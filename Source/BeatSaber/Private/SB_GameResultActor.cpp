// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_GameResultActor.h"
#include "SB_GameResultWidget.h"
#include <UMG/Public/Components/WidgetComponent.h>

// Sets default values
ASB_GameResultActor::ASB_GameResultActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<USB_GameResultWidget> tempGameResultFactory(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SB/Blueprints/WB_GameResult.WB_GameResult_C'"));
	if (tempGameResultFactory.Succeeded()) {
		gameResultFactory = tempGameResultFactory.Class;
	}

	gameResultWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("gameResultWidgetComp"));
	SetRootComponent(gameResultWidgetComp);

	gameResultWidgetComp->SetWidgetClass(gameResultFactory);
	gameResultWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ASB_GameResultActor::BeginPlay()
{
	Super::BeginPlay();
	
	gameResultWidgetInstance = Cast<USB_GameResultWidget>(gameResultWidgetComp->GetWidget());
}

// Called every frame
void ASB_GameResultActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

