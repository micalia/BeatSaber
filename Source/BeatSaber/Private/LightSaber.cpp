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

	sm_pointVal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PointVal"));
	sm_pointVal->SetupAttachment(sm_blade);
	sm_pointVal->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	sm_blade->OnComponentBeginOverlap.AddDynamic(this, &ALightSaber::OnStartOverlap_Blade);
	sm_blade->OnComponentEndOverlap.AddDynamic(this, &ALightSaber::OnEndOverlap_Blade);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> tempSliceMat(TEXT("/Script/Engine.Material'/Game/SB/Models/light-saber/source/02_-_Default.02_-_Default'"));

	if (tempSliceMat.Succeeded())
	{
		sliceMat = tempSliceMat.Object;
	}
	
}

// Called when the game starts or when spawned
void ALightSaber::BeginPlay()
{
	Super::BeginPlay();
	
	gm = Cast<AInGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void ALightSaber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 현재 액터의 위치와 이전 프레임에서의 위치를 가져옵니다.
	FVector CurrentLocation = sm_pointVal->GetComponentLocation();
	FVector PreviousLocation = PreviousFrameLocation;

	// 현재 프레임과 이전 프레임 사이의 거리 벡터를 계산합니다.
	FVector Dir = CurrentLocation - PreviousLocation;

	// 거리 벡터를 정규화하여 방향 벡터로 만듭니다.
	Dir.Normalize();

	// 원하는 작업 수행
	FRotator newRotator = UKismetMathLibrary::MakeRotFromYX(Dir, rootComp->GetUpVector());
	sm_pointVal->SetWorldRotation(newRotator);

	// 현재 위치를 이전 프레임 위치로 설정합니다.
	PreviousFrameLocation = CurrentLocation;

}

// Called to bind functionality to input
void ALightSaber::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ALightSaber::OnStartOverlap_Blade(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ANodeBlock* nodeBlock = Cast<ANodeBlock>(OtherActor);
	if (nodeBlock) {
		if (nodeBlock->bSlice) return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("StartOverlap_Blade")), true, FVector2D(1, 1));
	OtherCompPointer = Cast<UProceduralMeshComponent>(OtherComp);
}

void ALightSaber::OnEndOverlap_Blade(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ANodeBlock* nodeBlock = Cast<ANodeBlock>(OtherActor);
	if (nodeBlock) {
		if (nodeBlock->bSlice) return;
	}
	else {
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("EndOverlap_Blade")), true, FVector2D(1, 1));
	if (OtherCompPointer) {
		UProceduralMeshComponent* OutOtherHalfProcMesh;
		UMaterialInterface* mi = sliceMat;
		if (sm_pointVal) {
			UKismetProceduralMeshLibrary::SliceProceduralMesh(OtherCompPointer, sm_pointVal->GetComponentLocation(), sm_pointVal->GetUpVector(), true, OutOtherHalfProcMesh, EProcMeshSliceCapOption::CreateNewSectionForCap, mi);
			OutOtherHalfProcMesh->SetSimulatePhysics(true);
			OutOtherHalfProcMesh->AddImpulse(FVector(-300, 600, 300), FName(TEXT("NONE")), true);
			
			//각도 계산
			FVector p0 = sm_pointVal->GetComponentLocation();
			FVector p1 = p0 + sm_pointVal->GetRightVector() * 500;
			FVector swingDir = sm_pointVal->GetRightVector();

			float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(swingDir, nodeBlock->rootComp->GetUpVector() * -1)));

			float ScoreThreshold = 45.0f;
			if (Angle <= ScoreThreshold) {
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("ScoreUP!!!!!")), true, FVector2D(3, 3));
				gm->currCombo += 1;
			}
			else{
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("notScore")), true, FVector2D(3, 3));
				gm->currCombo = 0;
			}

			nodeBlock->bSlice = true;
			nodeBlock->proceduralMesh->SetSimulatePhysics(true);
			nodeBlock->proceduralMesh->AddImpulse(FVector(-300, -600, -300), FName("None"), true);
			nodeBlock->DelayDestroy();

			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("GM combo: %d"),  gm->currCombo), true, FVector2D(3, 3));

		}
	}
}

