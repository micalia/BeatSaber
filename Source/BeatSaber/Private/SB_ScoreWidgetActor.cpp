// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_ScoreWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "../Public/ScoreWidget.h"

// Sets default values
ASB_ScoreWidgetActor::ASB_ScoreWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UScoreWidget> tempScoreWidgetFactory(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SB/Blueprints/WB_ScoreWidget.WB_ScoreWidget_C'"));
	if (tempScoreWidgetFactory.Succeeded()) {
		scoreWidgetFactory = tempScoreWidgetFactory.Class;
	}

	scoreWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("scoreWidgetComp"));
	SetRootComponent(scoreWidgetComp);

	scoreWidgetComp->SetWidgetClass(scoreWidgetFactory);
	scoreWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ASB_ScoreWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	
	scoreWidgetInstance = Cast<UScoreWidget>(scoreWidgetComp->GetWidget());
}

// Called every frame
void ASB_ScoreWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

