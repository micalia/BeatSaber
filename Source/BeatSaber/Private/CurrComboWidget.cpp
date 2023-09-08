// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrComboWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
ACurrComboWidget::ACurrComboWidget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currComboUIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("currComboUIComp"));
	SetRootComponent(currComboUIComp);
}

// Called when the game starts or when spawned
void ACurrComboWidget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACurrComboWidget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

