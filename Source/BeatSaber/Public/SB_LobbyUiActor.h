// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_LobbyUiActor.generated.h"

UCLASS()
class BEATSABER_API ASB_LobbyUiActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASB_LobbyUiActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UWidgetComponent* compWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class USB_LobbyUI> LobbyUIfactory;

	UPROPERTY()
	class USB_LobbyUI* LobbyUIinstance;

	UPROPERTY()
	class UAudioComponent* audioComp;
};
