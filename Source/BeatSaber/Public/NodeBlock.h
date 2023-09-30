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

	UPROPERTY()
		class AInGameMode* gm;
public:
	//블럭 회전 값 (0~7)
	int blockRotate;
	UPROPERTY()
	UMaterialInstanceDynamic* CubeDynamicMaterial;
	int blockColor; // 0 : 빨강 , 1 : 파랑
	UFUNCTION()
	void SwitchColor(int num);
	// 0 : 화살표 / 1: 점
	UPROPERTY(VisibleAnywhere)
	int blockType;
	UFUNCTION()
	void SwitchType(int num);
public:
	//이동
	UPROPERTY(EditAnywhere)
	float speed = 700;

	void DelayDestroy();

private:
	class AEO_Sync* sync;

	UPROPERTY(EditDefaultsOnly)
		class USoundBase* tik;
};
