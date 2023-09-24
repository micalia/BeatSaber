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
	compWallMesh->SetCollisionProfileName(TEXT("NodeBlock"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> tempWallObstacle(TEXT("/Script/Engine.StaticMesh'/Game/SB/Models/WallObstacle/Qiang.Qiang'"));
	if (tempWallObstacle.Succeeded()) {
		compWallMesh->SetStaticMesh(tempWallObstacle.Object);
	}

	sync = Cast<AEO_Sync>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_Sync::StaticClass()));
}

void AWallObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (sync != nullptr)
	{
		if (sync->isGenerate && sync->bGameStart)
		{
			FVector p0 = GetActorLocation();
			FVector vt = FVector::ForwardVector * -1 * speed * DeltaTime;
			SetActorLocation(p0 + vt);
		}
	}
}
