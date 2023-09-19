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
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* widgetComp;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> gridNumWidget;

public:
	class AEO_RhythmNote* noteArr[3][4];

public:
	void SetActive(bool bCheck);
	void SetGridNumber(int num);
};
