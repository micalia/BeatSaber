#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EO_RhythmNote.generated.h"


UCLASS()
class BEATSABER_API AEO_RhythmNote : public AActor
{
	GENERATED_BODY()
	
public:	
	AEO_RhythmNote();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* meshComp;
	UPROPERTY(VisibleAnywhere)
	class UProceduralMeshComponent* proceduralMeshComp;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* matInterface;

	UPROPERTY(EditDefaultsOnly)
	float speed = 700;
	int myXPos = 0;
	int myYPos = 0;
	int colorIndex = 0;

private:
	UPROPERTY(VisibleAnywhere)
	class AEO_Sync* sync;
	UPROPERTY(VisibleAnywhere)
	class AEO_GridController* gridController;
	UPROPERTY(EditDefaultsOnly)
	class USoundBase* tik;

private:
	UMaterialInstanceDynamic* cubeDynamicMaterial;
	
	FVector syncPos;
	bool isTik = false;

private:
	void PatternTest(float deltaTime);
	void EditorSyncTest();

public:
	UFUNCTION()
	void SetNoteColor(int num);

};
