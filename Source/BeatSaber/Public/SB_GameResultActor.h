// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_GameResultActor.generated.h"

UCLASS()
class BEATSABER_API ASB_GameResultActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASB_GameResultActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class USB_GameResultWidget> gameResultFactory;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* gameResultWidgetComp;

	UPROPERTY()
	class USB_GameResultWidget* gameResultWidgetInstance;
};
