// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSaber.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "NodeBlock.h"
#include <Kismet/GameplayStatics.h>

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
}

// Called when the game starts or when spawned
void ALightSaber::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSaber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALightSaber::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ALightSaber::OnStartOverlap_Blade(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("StartOverlap_Blade")), true, FVector2D(1, 1));
	OtherCompPointer = Cast<UProceduralMeshComponent>(OtherComp);
}

void ALightSaber::OnEndOverlap_Blade(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("EndOverlap_Blade")), true, FVector2D(1, 1));
	if (OtherCompPointer) {
		//UProceduralMeshComponent* OutOtherHalfProcMesh;
		//UMaterialInterface* mi = nullptr;
		if (sm_pointVal) {
			/*UKismetProceduralMeshLibrary::SliceProceduralMesh(OtherCompPointer, sm_pointVal->GetComponentLocation(), sm_pointVal->GetUpVector(), true, OutOtherHalfProcMesh, EProcMeshSliceCapOption::CreateNewSectionForCap, mi);
			OutOtherHalfProcMesh->SetSimulatePhysics(true);
			OutOtherHalfProcMesh->AddImpulse(FVector(300), FName(TEXT("NONE")), true);*/
			
			//각도 계산
			FVector p0 = sm_pointVal->GetComponentLocation();
			FVector p1 = p0 + sm_pointVal->GetRightVector() *500;
			DrawDebugLine(GetWorld(),p0,p1 ,FColor::Blue, true, 30,0,3);
			FVector swingDir = sm_pointVal->GetRightVector();

			ANodeBlock* nodeBlock =Cast<ANodeBlock>(OtherActor);
			if (nodeBlock) {
				float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(swingDir, nodeBlock->rootComp->GetUpVector() * -1)));

				float ScoreThreshold = 45.0f;
				if (Angle <= ScoreThreshold) {
					GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("ScoreUP!!!!!")), true, FVector2D(1, 1));
				}
				else{
					GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("notScore")), true, FVector2D(1, 1));
				}
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("Angle: %f"),  Angle), true, FVector2D(1, 1));
			}


		}
	}
}

