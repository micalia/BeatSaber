// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeBlock.h"
#include "ProceduralMeshComponent.h"
#include <Components/StaticMeshComponent.h>

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
	proceduralMesh->SetCollisionProfileName(TEXT("BlockAll"));
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
}

// Called when the game starts or when spawned
void ANodeBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANodeBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

