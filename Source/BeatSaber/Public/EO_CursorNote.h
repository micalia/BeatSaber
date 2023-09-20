#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EO_CursorNote.generated.h"


UCLASS()
class BEATSABER_API AEO_CursorNote : public AActor
{
	GENERATED_BODY()
	
public:	
	AEO_CursorNote();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* rootSceneComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* meshComp;
	UPROPERTY(VisibleAnywhere)
	class UProceduralMeshComponent* proceduralMeshComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* bombMeshComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* wallMeshComp;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* matInterface;

private:
	UMaterialInstanceDynamic* cubeDynamicMaterial;

	UPROPERTY(EditAnywhere)
	float wallXscaleRatio = 0.135f;
	UPROPERTY(EditAnywhere)
	float wallZscaleRatio = 0.32f;

public:
	UFUNCTION()
	void SwitchNote(int num);
	UFUNCTION()
	void SwitchNoteType(int num);
};
