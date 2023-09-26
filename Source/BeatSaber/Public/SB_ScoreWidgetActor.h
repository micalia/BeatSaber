// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_ScoreWidgetActor.generated.h"

UCLASS()
class BEATSABER_API ASB_ScoreWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASB_ScoreWidgetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UScoreWidget> scoreWidgetFactory;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* scoreWidgetComp;

	UPROPERTY()
	class UScoreWidget* scoreWidgetInstance;
};
