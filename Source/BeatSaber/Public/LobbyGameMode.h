// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	UPROPERTY()
	class ASB_LobbyUiActor* lobbyUiActor;

	UPROPERTY()
	class USB_LobbyUI* lobbyUIinstance;

	void SetSelectMusicInfo(FString songName, FString artist, FString thumbPath);
};
