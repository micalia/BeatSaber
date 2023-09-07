// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralMeshComponent.h"
#include "LightSaber.h"
#include "KismetProceduralMeshLibrary.h"

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

	sm_point = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PointSM"));
	sm_point->SetupAttachment(sm_blade);
	sm_point->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

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

	if (sm_point) {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("NotNull")), true, FVector2D(1, 1));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("Null")), true, FVector2D(1, 1));
	}
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
		UProceduralMeshComponent* OutOtherHalfProcMesh;
		UMaterialInterface* mi = nullptr;
		if (sm_point) {
			UKismetProceduralMeshLibrary::SliceProceduralMesh(OtherCompPointer, sm_point->GetComponentLocation(), sm_point->GetUpVector(), true, OutOtherHalfProcMesh, EProcMeshSliceCapOption::CreateNewSectionForCap, mi);
			OutOtherHalfProcMesh->SetSimulatePhysics(true);
			OutOtherHalfProcMesh->AddImpulse(FVector(300), FName(TEXT("NONE")), true);
		}
	}
}

