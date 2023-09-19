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

	UPROPERTY(EditAnywhere)
	class UBoxComponent* compBox;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compWallMesh;

};
