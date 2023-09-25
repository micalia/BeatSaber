// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereObstacle.h"
#include "Components/SphereComponent.h"
#include <Components/StaticMeshComponent.h>
#include <GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionComponent.h>
#include <Kismet/GameplayStatics.h>
#include "EO_Sync.h"

ASphereObstacle::ASphereObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	compSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(compSphere);

	compSphereObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereObstacleMesh"));
	compSphereObstacleMesh->SetupAttachment(compSphere);
	compSphereObstacleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> tempSphereObstacle(TEXT("/Script/Engine.StaticMesh'/Game/SB/Models/SphereObstacle/Bomb.Bomb'"));
	if (tempSphereObstacle.Succeeded()) {
		compSphereObstacleMesh->SetStaticMesh(tempSphereObstacle.Object);
	}

	compGCSphereObstacle = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("compGC"));
	compGCSphereObstacle->SetupAttachment(compSphere);
	compGCSphereObstacle->SetVisibility(false);
	compGCSphereObstacle->SetSimulatePhysics(false);

	static ConstructorHelpers::FObjectFinder<UGeometryCollection> tempCompGCSphereObstacle(TEXT("/Script/GeometryCollectionEngine.GeometryCollection'/Game/SB/GC/GC_SphereObstacle.GC_SphereObstacle'"));
	if (tempCompGCSphereObstacle.Succeeded()) {
		compGCSphereObstacle->SetRestCollection(tempCompGCSphereObstacle.Object);
	}

	sync = Cast<AEO_Sync>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_Sync::StaticClass()));
}

void ASphereObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void ASphereObstacle::CrackEffect()
{
	compSphereObstacleMesh->SetVisibility(false);
	compGCSphereObstacle->SetVisibility(true);
	compGCSphereObstacle->SetSimulatePhysics(true);
	compGCSphereObstacle->ApplyExternalStrain(0, GetActorLocation(), 0, 0, 1, 1);

	FTimerHandle destroyDelay;
	GetWorld()->GetTimerManager().SetTimer(destroyDelay, FTimerDelegate::CreateLambda([&]() {
		Destroy();
		}), 2.3f, false);
}
