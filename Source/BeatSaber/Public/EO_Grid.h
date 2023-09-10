#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EO_Grid.generated.h"


UCLASS()
class BEATSABER_API AEO_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	AEO_Grid();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* meshComp;

private:
	/*UPROPERTY(VisibleAnywhere)
	class AGridController* gridController;*/

public:
	UPROPERTY(VisibleAnywhere)
	TArray<class AEO_RhythmNote*> placedNotes;

private:
	UPROPERTY(EditDefaultsOnly)
	float speed = 500;
};