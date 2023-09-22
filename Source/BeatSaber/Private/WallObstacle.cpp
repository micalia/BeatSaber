// Fill out your copyright notice in the Description page of Project Settings.


#include "WallObstacle.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>

AWallObstacle::AWallObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(rootComp);
	rootComp->SetRelativeLocation(FVector(-50, 0, 0));

	//compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	//compBox->SetRelativeLocation(FVector(-50,0,0));
	//compBox->SetWorldScale3D(FVector(1)); // 노트 블럭 사이즈로 스케일 조절
	//compBox->SetBoxExtent(FVector(238, 26, 100));
	//compBox->SetupAttachment(RootComponent);

	compWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	compWallMesh->SetupAttachment(RootComponent);
	compWallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	compWallMesh->SetRelativeLocation(FVector(0));
	compWallMesh->SetRelativeScale3D(FVector(wallXscaleRatio, wallYscaleRatio, wallZscaleRatio));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> tempWallObstacle(TEXT("/Script/Engine.StaticMesh'/Game/SB/Models/WallObstacle/Qiang.Qiang'"));
	if (tempWallObstacle.Succeeded()) {
		compWallMesh->SetStaticMesh(tempWallObstacle.Object);
	}
}
