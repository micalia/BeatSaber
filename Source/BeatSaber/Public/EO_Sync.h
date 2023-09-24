#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EO_Sync.generated.h"


UCLASS()
class BEATSABER_API AEO_Sync : public AActor
{
	GENERATED_BODY()
	
public:	
	AEO_Sync();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadOnly)
	class UAudioComponent* audioComp;

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ANodeBlock> noteFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASphereObstacle> bombFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWallObstacle> wallFactory;
	UPROPERTY(EditDefaultsOnly)
	class USoundBase* testSound;
	UPROPERTY(VisibleAnywhere)
	class UDataTable* patternData;

public:
	float musicBPM;
	float frequeny;
	float offset = 0;
	float sampleOffset;

	float oneBeatTime;
	float nextSample;

	float barPerSec;

	int32 startPos = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 playTime = 0;
	
	float delayTime = 0;

	bool isGenerate = false;
	bool bGameStart = false;

private:
	class AVR_Player* player;
	class AInGameMode* gameModeBase;

private:
	void MusicPlay();
	void GenerateNote();
	float XGeneratePos(int rowX);
	float YGeneratePos(int rowY);
};
