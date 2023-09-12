// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LightSaber.generated.h"

UCLASS()
class BEATSABER_API ALightSaber : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALightSaber();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* sm_blade;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* sm_pointVal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* sm_handle;

	UPROPERTY()
	class UProceduralMeshComponent* OtherCompPointer;

	UPROPERTY(EditAnywhere, Category = "Materials")
    class UMaterialInterface* sliceMat;

public:
	UPROPERTY()
	class AInGameMode* gm;

	FVector PreviousFrameLocation;
};
