// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "SphereObstacle.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API ASphereObstacle : public AObstacle
{
	GENERATED_BODY()
public:
	ASphereObstacle();

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USphereComponent* compSphere;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compSphereObstacleMesh;
	UPROPERTY(EditAnywhere)
	class UGeometryCollectionComponent* compGCSphereObstacle;

	void CrackEffect();

	UPROPERTY(EditAnywhere)
	float speed = 700;

private:
	class AEO_Sync* sync;
};
