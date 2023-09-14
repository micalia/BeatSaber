// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeBlock.h"
#include "ProceduralMeshComponent.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Materials/MaterialInstanceDynamic.h>
#include <Kismet/KismetMaterialLibrary.h>

// Sets default values
ANodeBlock::ANodeBlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("rootComp"));
	SetRootComponent(rootComp);

	proceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("proceduralMesh"));
	proceduralMesh->SetupAttachment(rootComp);
	proceduralMesh->SetRelativeLocation(FVector(0, 0, -100));
	proceduralMesh->SetRelativeRotation(FRotator(0, 90, 0));
	proceduralMesh->SetCollisionProfileName(TEXT("NodeBlock"));
	proceduralMesh->bUseComplexAsSimpleCollision = false;

	sm_nodeBlock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sm_nodeBlock"));
	sm_nodeBlock->SetupAttachment(rootComp);
	sm_nodeBlock->SetRelativeLocation(FVector(0, 0, -100));
	sm_nodeBlock->SetRelativeRotation(FRotator(0, 90, 0));
	sm_nodeBlock->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	sm_nodeBlock->bHiddenInGame = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> tempNodeBlockMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/RedNoteBlock.RedNoteBlock'"));
	if (tempNodeBlockMesh.Succeeded()) {
		sm_nodeBlock->SetStaticMesh(tempNodeBlockMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> tempBlockMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/SB/Materials/M_Cube_Inst.M_Cube_Inst'"));

	if (tempBlockMat.Succeeded())
	{
		blockMat = tempBlockMat.Object;
	}

}

// Called when the game starts or when spawned
void ANodeBlock::BeginPlay()
{
	Super::BeginPlay();

	sm_nodeBlock->SetMaterial(0, blockMat);
	CubeDynamicMaterial = UMaterialInstanceDynamic::Create(sm_nodeBlock->GetMaterial(0), this);
	sm_nodeBlock->SetMaterial(0, CubeDynamicMaterial);
	proceduralMesh->SetMaterial(0, CubeDynamicMaterial);

	blockColor = UKismetMathLibrary::RandomIntegerInRange(0, 1);
	SwitchColor(blockColor);
	
	blockRotate = UKismetMathLibrary::RandomInteger64InRange(0, 7);

	switch (blockRotate)
	{
		case 0: // 0도 아래
		{
			SetActorRotation(FRotator(0, 0, 0));
			break;
		}
		case 1: // 45도 아래 왼쪽 대각선
		{
			SetActorRotation(FRotator(0, 0, 45));
			break;
		}
		case 2: // 90도 
		{
			SetActorRotation(FRotator(0, 0, 90));
			break;
		}
		case 3: // 135도 
		{
			SetActorRotation(FRotator(0, 0, 135));
			break;
		}
		case 4: // 180도 
		{
			SetActorRotation(FRotator(0, 0, 180));
			break;
		}
		case 5: // 225도 
		{
			SetActorRotation(FRotator(0, 0, 225));
			break;
		}
		case 6: // 270도
		{
			SetActorRotation(FRotator(0, 0, 270));
			break;
		}
		case 7: // 315도 
		{
			SetActorRotation(FRotator(0, 0, 315));
			break;
		}
	}

}

// Called every frame
void ANodeBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bSlice) {
		FVector p0 = GetActorLocation();
		FVector vt = FVector::ForwardVector * -1 * speed * DeltaTime;
		SetActorLocation(p0 + vt);
	}

}

void ANodeBlock::SwitchColor(int num)
{
	switch (num)
	{
	case 0: // 빨강
		if (CubeDynamicMaterial) {
			CubeDynamicMaterial->SetScalarParameterValue(TEXT("ColorChoice"), 1);
		}
		break;
	case 1: // 파랑
		if (CubeDynamicMaterial) {
			CubeDynamicMaterial->SetScalarParameterValue(TEXT("ColorChoice"), 0);
		}
		break;
	}
}

void ANodeBlock::DelayDestroy()
{
	FTimerHandle destroyDelay;
	GetWorld()->GetTimerManager().SetTimer(destroyDelay, FTimerDelegate::CreateLambda([&]() {
		Destroy();
		}), 3, false);
}

