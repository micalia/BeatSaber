// Fill out your copyright notice in the Description page of Project Settings.


#include "WallObstacle.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>

AWallObstacle::AWallObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	compBox->SetBoxExtent(FVector(238, 26, 100));
	SetRootComponent(compBox);

	compWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	compWallMesh->SetupAttachment(compBox);
	compWallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	compWallMesh->SetRelativeLocation(FVector(238, 0, 0));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> tempWallObstacle(TEXT("/Script/Engine.StaticMesh'/Game/SB/Models/WallObstacle/Qiang.Qiang'"));
	if (tempWallObstacle.Succeeded()) {
		compWallMesh->SetStaticMesh(tempWallObstacle.Object);
	}
}
