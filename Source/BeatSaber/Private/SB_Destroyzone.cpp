// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_Destroyzone.h"
#include "Components/BoxComponent.h"
#include "NodeBlock.h"
#include "InGameMode.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
// Sets default values
ASB_Destroyzone::ASB_Destroyzone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(compBox);
}

// Called when the game starts or when spawned
void ASB_Destroyzone::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	gameMode = Cast<AInGameMode>(GetWorld()->GetAuthGameMode());
	if (compBox) {
		compBox->OnComponentBeginOverlap.AddDynamic(this, &ASB_Destroyzone::OnOverlap);
	}
}

// Called every frame
void ASB_Destroyzone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASB_Destroyzone::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ANodeBlock* nodeBlock = Cast<ANodeBlock>(OtherActor);
	if (nodeBlock) {
		if (!nodeBlock->bSlice) {
			gameMode->currCombo = 0;
			if (player) {
				player->currHp--;
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("Hp decrease")), true, FVector2D(1, 1));
			}
			nodeBlock->DelayDestroy();
		}
	}

}

