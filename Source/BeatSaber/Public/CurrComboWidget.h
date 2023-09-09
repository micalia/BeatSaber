// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CurrComboWidget.generated.h"

UCLASS()
class BEATSABER_API ACurrComboWidget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACurrComboWidget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UComboWidget> comboWidgetFactory;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* currComboUIComp;

	UPROPERTY()
	class UComboWidget* comboWidgetInstance;
};
