// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSaber.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "NodeBlock.h"
#include <Kismet/GameplayStatics.h>
#include "InGameMode.h"
#include <Kismet/KismetMathLibrary.h>
#include "VR_Player.h"
#include <Sound/SoundBase.h>
#include "SphereObstacle.h"
#include <Particles/ParticleSystem.h>

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

	static ConstructorHelpers::FObjectFinder<USoundBase> tempHitSound(TEXT("/Script/Engine.SoundWave'/Game/SB/Sounds/hitEffectSound.hitEffectSound'"));

	if (tempHitSound.Succeeded())
	{
		hitCutSound = tempHitSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> tempBadCutSound(TEXT("/Script/Engine.SoundWave'/Game/SB/Sounds/badCut.badCut'"));

	if (tempBadCutSound.Succeeded())
	{
		badCutSound = tempBadCutSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> tempRedDestroyEffect(TEXT("/Script/Engine.ParticleSystem'/Game/SB/particle/ParticleSpark_red.ParticleSpark_red'"));

	if (tempRedDestroyEffect.Succeeded())
	{
		redDestroyEffect = tempRedDestroyEffect.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> tempBlueDestroyEffect(TEXT("/Script/Engine.ParticleSystem'/Game/SB/particle/ParticleSpark_Blue.ParticleSpark_Blue'"));

	if (tempBlueDestroyEffect.Succeeded())
	{
		blueDestroyEffect = tempBlueDestroyEffect.Object;
	}
}

// Called when the game starts or when spawned
void ALightSaber::BeginPlay()
{
	Super::BeginPlay();
	
	SliceCubeDynamicMaterial = UMaterialInstanceDynamic::Create(sliceMat, this);
	gm = Cast<AInGameMode>(GetWorld()->GetAuthGameMode());
	if (gm && gm->player) {
		SetOwner(Cast<AActor>(gm->player));
	}
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
		AVR_Player* player = Cast<AVR_Player>(GetOwner());

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

				UProceduralMeshComponent* proceduralMesh = Cast<UProceduralMeshComponent>(HitResult[i].Component);
				if (proceduralMesh) {
					UProceduralMeshComponent* OutOtherHalfProcMesh;
					//잘라진 단면 색깔
					if(nodeBlock->blockColor == 0) {  // 빨강
						SliceCubeDynamicMaterial->SetScalarParameterValue(TEXT("ColorChoice"), 1);
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), redDestroyEffect, nodeBlock->GetActorLocation(), nodeBlock->GetActorRotation(), FVector(0.3f));
					}
					else if(nodeBlock->blockColor == 1) { // 파랑
						SliceCubeDynamicMaterial->SetScalarParameterValue(TEXT("ColorChoice"), 0);
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), blueDestroyEffect, nodeBlock->GetActorLocation(), nodeBlock->GetActorRotation(), FVector(0.3f));
					}
					UMaterialInterface* mi = SliceCubeDynamicMaterial;
					if (sm_pointVal) {
						UKismetProceduralMeshLibrary::SliceProceduralMesh(proceduralMesh, sm_pointVal->GetComponentLocation(), sm_pointVal->GetUpVector(), true, OutOtherHalfProcMesh, EProcMeshSliceCapOption::CreateNewSectionForCap, mi);
						OutOtherHalfProcMesh->SetSimulatePhysics(true);
						OutOtherHalfProcMesh->SetCollisionProfileName(TEXT("NodeBlock"));
						OutOtherHalfProcMesh->AddImpulse(FVector(150, 600, 300), FName(TEXT("NONE")), true);

						//각도 계산
						FVector p0 = sm_pointVal->GetComponentLocation();
						FVector p1 = p0 + sm_pointVal->GetRightVector() * 500;
						FVector swingDir = sm_pointVal->GetRightVector();

						float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(swingDir, nodeBlock->rootComp->GetUpVector() * -1)));

						float ScoreThreshold = 45.0f;

						//점수 판정
						if (nodeBlock->blockType == 0) { // 화살표
							if (Angle <= ScoreThreshold) {
								if ((int8)saberColor == nodeBlock->blockColor) {
									UGameplayStatics::PlaySound2D(GetWorld(), hitCutSound, 0.5f);
									gm->currCombo += 1;
									gm->score+=10;
									if (player) {
										player->currHp++;
										if (player->currHp > player->fullHp) {
											player->currHp = player->fullHp;
										}
									}
								}
								else {
									if (player) {
										player->currHp--;
									}
									UGameplayStatics::PlaySound2D(GetWorld(), badCutSound, 0.5f);
									gm->currCombo = 0;
								}
							}
							else {
								if (player) {
									player->currHp--;
								}
								UGameplayStatics::PlaySound2D(GetWorld(), badCutSound, 0.5f);
								gm->currCombo = 0;
							}
						}
						else {// 화살표 없는 블럭
							if ((int8)saberColor == nodeBlock->blockColor) {
								UGameplayStatics::PlaySound2D(GetWorld(), hitCutSound, 0.5f);
								gm->currCombo += 1;
								gm->score += 10;
								if (player) {
									player->currHp++;
									if (player->currHp > player->fullHp) {
										player->currHp = player->fullHp;
									}
								}
							}
							else {
								if (player) {
									player->currHp--;
								}
								UGameplayStatics::PlaySound2D(GetWorld(), badCutSound, 0.5f);
								gm->currCombo = 0;
							}
						}

						nodeBlock->proceduralMesh->SetSimulatePhysics(true);
						nodeBlock->proceduralMesh->AddImpulse(FVector(150, -600, -300), FName("None"), true);
						nodeBlock->DelayDestroy();

				}
			}

			}else{
				ASphereObstacle* sphereObstacle = Cast<ASphereObstacle>(HitResult[i].GetActor());
				if (sphereObstacle) {
					sphereObstacle->CrackEffect();
					player->currHp--;
					gm->currCombo = 0;
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


