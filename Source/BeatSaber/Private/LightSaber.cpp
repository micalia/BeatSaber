// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSaber.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "NodeBlock.h"
#include <Kismet/GameplayStatics.h>
#include "InGameMode.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ALightSaber::ALightSaber()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("rootComp"));
	SetRootComponent(rootComp);

	sm_blade = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade"));
	sm_blade->SetupAttachment(rootComp);
	sm_blade->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	sm_blade->SetRelativeLocation(FVector(0,0, -15));
	sm_blade->SetRelativeScale3D(FVector(0.06, 0.06, 0.1));

	sm_pointVal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PointVal"));
	sm_pointVal->SetupAttachment(sm_blade);
	sm_pointVal->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	sm_pointVal->SetRelativeLocation(FVector(0, 0, 790));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> tempSliceMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/SB/Materials/M_crosssection_Inst.M_crosssection_Inst'"));

	if (tempSliceMat.Succeeded())
	{
		sliceMat = tempSliceMat.Object;
	}
	
	sm_handle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Handle"));
	sm_handle->SetupAttachment(rootComp);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> tempSmHandleMesh(TEXT("/Script/Engine.StaticMesh'/Game/SB/Meshes/SaberHandle.SaberHandle'"));

	if (tempSmHandleMesh.Succeeded())
	{
		sm_handle->SetStaticMesh(tempSmHandleMesh.Object);
	}
	
	sm_handle->SetRelativeScale3D(FVector(0.06, 0.06, 0.055));
	sm_handle->SetRelativeLocation(FVector(0,0,-5));
}

// Called when the game starts or when spawned
void ALightSaber::BeginPlay()
{
	Super::BeginPlay();
	
	SliceCubeDynamicMaterial = UMaterialInstanceDynamic::Create(sliceMat, this);
	gm = Cast<AInGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void ALightSaber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = sm_pointVal->GetComponentLocation();
	FVector PreviousLocation = PreviousFrameLocation;
	FVector Dir = CurrentLocation - PreviousLocation;

	Dir.Normalize();

	FRotator newRotator = UKismetMathLibrary::MakeRotFromYX(Dir, rootComp->GetUpVector());
	sm_pointVal->SetWorldRotation(newRotator);

	FVector halfSize = FVector(73,4,4);
	TArray<AActor*> EmptyActorsToIgnore;
	TArray<FHitResult> HitResult;

	bool bSliceChk = UKismetSystemLibrary::BoxTraceMulti(
		GetWorld(),
		CurrentLocation,
		PreviousLocation,
		halfSize,
		newRotator,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel3),
		false,
		EmptyActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		0.1
	);

	if (bSliceChk) {
		for (int32 i =0; i<HitResult.Num();i++)
		{
			ANodeBlock* nodeBlock = Cast<ANodeBlock>(HitResult[i].GetActor());
			if (nodeBlock) {
				if (nodeBlock->bSlice){
					continue;
				}
				else {
					nodeBlock->bSlice = true;
				}
			}else{
				continue;
			}
			UProceduralMeshComponent* proceduralMesh = Cast<UProceduralMeshComponent>(HitResult[i].Component);
			if (proceduralMesh) {
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("YYYYYYYYY")), true, FVector2D(3, 3));
				UProceduralMeshComponent* OutOtherHalfProcMesh;
				if(nodeBlock->blockColor == 0) {  // »¡°­
					SliceCubeDynamicMaterial->SetScalarParameterValue(TEXT("ColorChoice"), 0);
				}
				else if(nodeBlock->blockColor == 1) { // ÆÄ¶û
					SliceCubeDynamicMaterial->SetScalarParameterValue(TEXT("ColorChoice"), 1);
				}
				UMaterialInterface* mi = SliceCubeDynamicMaterial;
				if (sm_pointVal) {
					FVector BoxCenter = nodeBlock->GetActorLocation();
					FVector CutterOffsetVector = sm_pointVal->GetUpVector();
					FVector AdjustedCutterOffsetVector = GetActorRotation().UnrotateVector(CutterOffsetVector);

					UKismetProceduralMeshLibrary::SliceProceduralMesh(proceduralMesh, sm_pointVal->GetComponentLocation(), sm_pointVal->GetUpVector(), true, OutOtherHalfProcMesh, EProcMeshSliceCapOption::CreateNewSectionForCap, mi);
					OutOtherHalfProcMesh->SetSimulatePhysics(true);
					OutOtherHalfProcMesh->SetCollisionProfileName(TEXT("NodeBlock"));
					OutOtherHalfProcMesh->AddImpulse(FVector(-550, 700, 400), FName(TEXT("NONE")), true);

					//°¢µµ °è»ê
					FVector p0 = sm_pointVal->GetComponentLocation();
					FVector p1 = p0 + sm_pointVal->GetRightVector() * 500;
					FVector swingDir = sm_pointVal->GetRightVector();

					float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(swingDir, nodeBlock->rootComp->GetUpVector() * -1)));

					float ScoreThreshold = 45.0f;
					if (Angle <= ScoreThreshold) {
						GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("ScoreUP!!!!!")), true, FVector2D(3, 3));
						gm->currCombo += 1;
					}
					else {
						GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("notScore")), true, FVector2D(3, 3));
						gm->currCombo = 0;
					}

					nodeBlock->proceduralMesh->SetSimulatePhysics(true);
					nodeBlock->proceduralMesh->AddImpulse(FVector(-550, -700, -400), FName("None"), true);
					nodeBlock->DelayDestroy();

					GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("GM combo: %d"), gm->currCombo), true, FVector2D(3, 3));
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("NNNNNNNNN")), true, FVector2D(3, 3));
			}
		}
		}
	}

	PreviousFrameLocation = CurrentLocation;

}

// Called to bind functionality to input
void ALightSaber::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


