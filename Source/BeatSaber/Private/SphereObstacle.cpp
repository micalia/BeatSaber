// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereObstacle.h"
#include "Components/SphereComponent.h"
#include <Components/StaticMeshComponent.h>

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
}
