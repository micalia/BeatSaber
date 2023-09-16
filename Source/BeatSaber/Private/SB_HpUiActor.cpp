// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_HpUiActor.h"
#include "SB_HpUiWidget.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "VR_Player.h"
#include <UMG/Public/Components/ProgressBar.h>

// Sets default values
ASB_HpUiActor::ASB_HpUiActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<USB_HpUiWidget> tempHpbarWidgetFactory(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SB/Blueprints/WB_HpUi.WB_HpUi_C'"));
	if (tempHpbarWidgetFactory.Succeeded()) {
		hpbarWidgetFactory = tempHpbarWidgetFactory.Class;
	}

	currHpUIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("currHpUIComp"));
	SetRootComponent(currHpUIComp);

	currHpUIComp->SetWidgetClass(hpbarWidgetFactory);
	currHpUIComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ASB_HpUiActor::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	comboHpbarInstance = Cast<USB_HpUiWidget>(currHpUIComp->GetWidget());
}

// Called every frame
void ASB_HpUiActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (player != nullptr && comboHpbarInstance != nullptr) {
		comboHpbarInstance->HpBar->SetPercent(player->currHp / player->fullHp);
	}
}

