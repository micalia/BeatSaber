// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NodeBlock.generated.h"

UENUM(BlueprintType)
enum class EBlockColor :uint8 {
	Red,
	Blue,
};

UCLASS()
class BEATSABER_API ANodeBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UProceduralMeshComponent* proceduralMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* sm_nodeBlock;

	UPROPERTY(BlueprintReadOnly)
	bool bSlice;

	UPROPERTY(EditAnywhere, Category = "Materials")
		class UMaterialInterface* blockMat;

public:
	//블럭 회전 값 (0~7)
	int blockRotate;
	
	int blockColor;

public:
	//이동
	UPROPERTY(EditAnywhere)
	float speed = 700;

	void DelayDestroy();
};
