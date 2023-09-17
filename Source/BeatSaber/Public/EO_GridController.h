#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EO_GridController.generated.h"


UCLASS()
class BEATSABER_API AEO_GridController : public APawn
{
	GENERATED_BODY()

public:
	AEO_GridController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadOnly)
	class UAudioComponent* audioComp;
	
public:
	UPROPERTY(EditDefaultsOnly, Category="Settings|Sounds")
	class USoundBase* musicSound;
	UPROPERTY(EditDefaultsOnly, Category="Settings|Generate")
	TSubclassOf<class AActor> gridTemplate;
	UPROPERTY(EditDefaultsOnly, Category="Settings|Generate")
	TSubclassOf<class AEO_Grid> gridFactory;
	UPROPERTY(EditDefaultsOnly, Category="Settings|Generate")
	TSubclassOf<class AEO_RhythmNote> noteFactory;
	UPROPERTY(EditDefaultsOnly, Category="Settings|Generate")
	TSubclassOf<class AEO_CursorNote> cursorFactory;

private:
	float musicBPM;
	float frequeny;
	float offset = 0;
	float sampleOffset;

	float oneBeatTime;
	float nextSample;

	float barPerSec;

	float speed = 700;

	FVector endGridPos;

	class AEO_CursorNote* tempNote = nullptr;
	class AEO_Grid* currentGrid = nullptr;

	int yArrIndex = 0;
	int xArrIndex = 2;
	float zPos = 0;
	int colorIndex = 0;
	int typeIndex = 0;

	int bitIndex = 0;

	UPROPERTY(VisibleAnywhere, Category="Settings|Grid")
	TArray<class AEO_Grid*> arr4BitGrid;
	UPROPERTY(VisibleAnywhere, Category="Settings|Grid")
	TArray<class AEO_Grid*> arr8BitGrid;
	UPROPERTY(VisibleAnywhere, Category="Settings|Grid")
	TArray<class AEO_Grid*> arr16BitGrid;

public:
	bool isPlaying = false;

	FVector syncPos;

private:
	void MakeGrid();
	void MoveGrid(float value);
	void PlacedNote();
	void RemoveNote();
	void NodeLeftRotation();
	void NodeRightRotation();
	void NodeUp();
	void NodeDown();
	void BitUp();
	void BitDown();
	void ChangeRedColor();
	void ChangeBlueColor();
	void ChangeNoteType();

	void SoundPlay();
	void OutData();
};
