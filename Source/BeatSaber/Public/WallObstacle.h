// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "WallObstacle.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API AWallObstacle : public AObstacle
{
	GENERATED_BODY()

public:
	AWallObstacle();

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USceneComponent* rootComp;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* compBox;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compWallMesh;

	UPROPERTY(EditAnywhere)
	float wallXscaleRatio = 0.21f;
	UPROPERTY(EditAnywhere)
	float wallYscaleRatio = 1.4f;
	UPROPERTY(EditAnywhere)
	float wallZscaleRatio = 0.5f;

	UPROPERTY(EditAnywhere)
	float speed = 700;

private:
	class AEO_Sync* sync;
};
