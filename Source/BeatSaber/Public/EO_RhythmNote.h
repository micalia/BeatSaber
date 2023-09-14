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

	UPROPERTY(EditDefaultsOnly)
	float speed = 500;
	int myXPos = 0;
	int myYPos = 0;

private:
	UPROPERTY(VisibleAnywhere)
	class AEO_Sync* sync;
};
