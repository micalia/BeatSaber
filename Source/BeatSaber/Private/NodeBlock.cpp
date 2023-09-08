// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeBlock.h"
#include "ProceduralMeshComponent.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/KismetMathLibrary.h>

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
	
	 int32 rand = UKismetMathLibrary::RandomInteger64InRange(0,7);

	 switch (rand)
	 {
		case 0: // 0µµ ¾Æ·¡
			{
				SetActorRotation(FRotator(0, 0, 0));
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("0 de")), true, FVector2D(1, 1));
				break;
			}
		case 1: // 45µµ ¾Æ·¡ ¿ÞÂÊ ´ë°¢¼±
			{
			SetActorRotation(FRotator(0, 0, 45));
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("45 de")), true, FVector2D(1, 1));
			break;
			}
		case 2: // 90µµ ¿ÞÂÊ
			{
			SetActorRotation(FRotator(0, 0, 90));
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("90 de")), true, FVector2D(1, 1));
			break;
			}
		case 3: // 135µµ ¿ÞÂÊ
			{
			SetActorRotation(FRotator(0, 0, 135));
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("135 de")), true, FVector2D(1, 1));
			break;
			}
		case 4: // 180µµ ¿ÞÂÊ
			{
			SetActorRotation(FRotator(0, 0, 180));
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("180 de")), true, FVector2D(1, 1));
			break;
			}
		case 5: // 225µµ ¿ÞÂÊ
			{
			SetActorRotation(FRotator(0, 0, 225));
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("225 de")), true, FVector2D(1, 1));
			break;
			}
		case 6: // 270µµ ¿ÞÂÊ
			{
			SetActorRotation(FRotator(0, 0, 270));
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("270 de")), true, FVector2D(1, 1));
			break;
			}
		case 7: // 315µµ ¿ÞÂÊ
			{
			SetActorRotation(FRotator(0, 0, 315));
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("315 de")), true, FVector2D(1, 1));
			break;
			}
	 }

}

// Called every frame
void ANodeBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

