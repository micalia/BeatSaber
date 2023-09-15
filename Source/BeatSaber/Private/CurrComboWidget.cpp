// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrComboWidget.h"
#include "Components/WidgetComponent.h"
#include "ComboWidget.h"

// Sets default values
ACurrComboWidget::ACurrComboWidget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UComboWidget> tempComboWidgetFactory(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SB/Blueprints/WB_ComboWidget.WB_ComboWidget_C'"));
	if (tempComboWidgetFactory.Succeeded()) {
		comboWidgetFactory = tempComboWidgetFactory.Class;
	}

	currComboUIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("currComboUIComp"));
	SetRootComponent(currComboUIComp);

	currComboUIComp->SetWidgetClass(comboWidgetFactory);
	currComboUIComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ACurrComboWidget::BeginPlay()
{
	Super::BeginPlay();
	
	comboWidgetInstance = Cast<UComboWidget>(currComboUIComp->GetWidget());
}

// Called every frame
void ACurrComboWidget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

