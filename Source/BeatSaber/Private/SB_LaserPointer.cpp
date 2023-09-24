// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_LaserPointer.h"
#include <Components/SkeletalMeshComponent.h>
#include <UMG/Public/Components/WidgetInteractionComponent.h>

// Sets default values
ASB_LaserPointer::ASB_LaserPointer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("rootComp"));
	SetRootComponent(rootComp);

	sm_RemoteController = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("sm_RemoteController"));
	sm_RemoteController->SetupAttachment(rootComp);

	laserPos = CreateDefaultSubobject<USceneComponent>(TEXT("laserPos"));
	laserPos->SetupAttachment(sm_RemoteController);

	interactionComp = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("interactionComp"));
	interactionComp->SetupAttachment(laserPos);
}

// Called when the game starts or when spawned
void ASB_LaserPointer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASB_LaserPointer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

