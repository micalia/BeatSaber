// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_LobbyUiActor.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "SB_LobbyUI.h"

// Sets default values
ASB_LobbyUiActor::ASB_LobbyUiActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<USB_LobbyUI> tempLobbyUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SB/Blueprints/WB_LobbyUI.WB_LobbyUI_C'"));
	if (tempLobbyUI.Succeeded()) {
		LobbyUIfactory = tempLobbyUI.Class;
	}

	compWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("compWidget"));
	SetRootComponent(compWidget);

	compWidget->SetWidgetClass(LobbyUIfactory);
	compWidget->SetDrawSize(FVector2D(1800, 900));
	compWidget->SetGeometryMode(EWidgetGeometryMode::Cylinder);
	compWidget->SetCylinderArcAngle(80);
}

// Called when the game starts or when spawned
void ASB_LobbyUiActor::BeginPlay()
{
	Super::BeginPlay();
	
	LobbyUIinstance = Cast<USB_LobbyUI>(compWidget->GetWidget());
}

// Called every frame
void ASB_LobbyUiActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

