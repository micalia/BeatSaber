// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "InGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "EO_Sync.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	sync = Cast<AEO_Sync>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_Sync::StaticClass()));
	gm = Cast<AInGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (gm) {
		if (gm->bGameEnd) {
			FVector p0 = GetActorLocation();
			FVector vt = FVector::UpVector * -1 * speed * 0.7f * DeltaTime;
			SetActorLocation(p0 + vt);
			return;
		}
	}

	if (sync != nullptr)
	{
		if (sync->isGenerate && sync->bGameStart)
		{
			FVector p0 = GetActorLocation();
			FVector vt = FVector::ForwardVector * -1 * speed * DeltaTime;
			SetActorLocation(p0 + vt);
		}
	}
}

