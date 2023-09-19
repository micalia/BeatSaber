// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Player.h"
#include <Camera/CameraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <HeadMountedDisplay/Public/MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/TextRenderComponent.h>
#include <Components/SphereComponent.h>

// Sets default values
AVR_Player::AVR_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cam->SetupAttachment(RootComponent);

	headMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	headMesh->SetupAttachment(cam);
	headMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	headCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HeadCollision"));
	headCollision->SetupAttachment(cam);

	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	leftController->SetupAttachment(RootComponent);
	// 모션 소스 선택
	leftController->MotionSource = "Left";

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHand"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	leftHand->SetRelativeRotation(FRotator(-25.0f, 180.0f, 90.0f));

	leftLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log Text"));
	leftLog->SetupAttachment(leftController);
	leftLog->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	leftLog->SetTextRenderColor(FColor::Yellow);
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);

	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	rightController->SetupAttachment(RootComponent);
	rightController->MotionSource = "Right";

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	rightHand->SetRelativeRotation(FRotator(25.0f, 0.0f, 90.0f));

	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log Text"));
	rightLog->SetupAttachment(rightController);
	rightLog->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	rightLog->SetTextRenderColor(FColor::Yellow);
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);

	bUseControllerRotationPitch = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	ConstructorHelpers::FClassFinder<AActor> tempLeftSaber(TEXT("/Script/Engine.Blueprint'/Game/SB/Blueprints/BP_LeftLightSaber.BP_LeftLightSaber_C'"));
	if (tempLeftSaber.Succeeded()) {
		leftSaberFactory = tempLeftSaber.Class;
	}

	ConstructorHelpers::FClassFinder<AActor> tempRightSaber(TEXT("/Script/Engine.Blueprint'/Game/SB/Blueprints/BP_RightLightSaber.BP_RightLightSaber_C'"));
	if (tempRightSaber.Succeeded()) {
		rightSaberFactory = tempRightSaber.Class;
	}

	rightSword = CreateDefaultSubobject<UChildActorComponent>(TEXT("RightSword"));
	rightSword->SetupAttachment(rightController);
	rightSword->SetChildActorClass(rightSaberFactory);
	rightSword->SetRelativeLocation(FVector(26.6, -2.3, -9.4));
	rightSword->SetRelativeRotation(FRotator(-78.8, 180, 180));

	leftSword = CreateDefaultSubobject<UChildActorComponent>(TEXT("LeftSword"));
	leftSword->SetupAttachment(leftController);
	leftSword->SetChildActorClass(leftSaberFactory);
	leftSword->SetRelativeLocation(FVector(26.6, 2.3, -9.4));
	leftSword->SetRelativeRotation(FRotator(-78.8, 180, 180));
}

// Called when the game starts or when spawned
void AVR_Player::BeginPlay()
{
	Super::BeginPlay();

	headCollision->OnComponentBeginOverlap.AddDynamic(this, &AVR_Player::OnOverlap);
	headCollision->OnComponentEndOverlap.AddDynamic(this, &AVR_Player::OnEndOverlap);
}

// Called every frame
void AVR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPlayerChk) {
		currTime += DeltaTime;
		if (currTime > decreaseDelayTime) {
			currTime = 0;
			currHp--;
		}
	}
}

// Called to bind functionality to input
void AVR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AVR_Player::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	crashWallCount++;
	bPlayerChk = true;
}

void AVR_Player::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	crashWallCount--;
	if (crashWallCount <= 0) {
		bPlayerChk = false;
	}
}
