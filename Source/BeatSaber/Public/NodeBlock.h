// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NodeBlock.generated.h"

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
public:
	//¿Ãµø
	UPROPERTY(EditAnywhere)
	float speed = 700;

	void DelayDestroy();
};
