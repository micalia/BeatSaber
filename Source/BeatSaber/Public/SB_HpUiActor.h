// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_HpUiActor.generated.h"

UCLASS()
class BEATSABER_API ASB_HpUiActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASB_HpUiActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class USB_HpUiWidget> hpbarWidgetFactory;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* currHpUIComp;

	UPROPERTY()
	class USB_HpUiWidget* comboHpbarInstance;

	UPROPERTY()
	class AVR_Player* player;
};
