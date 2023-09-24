// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_LaserPointer.generated.h"

UCLASS()
class BEATSABER_API ASB_LaserPointer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASB_LaserPointer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USceneComponent* rootComp;
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* sm_RemoteController;
	UPROPERTY(EditAnywhere)
	class USceneComponent* laserPos;
	UPROPERTY(EditAnywhere)
	class UWidgetInteractionComponent* interactionComp;

};
