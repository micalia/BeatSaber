// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VR_Player.generated.h"

UCLASS()
class BEATSABER_API AVR_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVR_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UCameraComponent* cam;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class USphereComponent* headCollision;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UStaticMeshComponent* headMesh;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UMotionControllerComponent* leftController;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class USkeletalMeshComponent* leftHand;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UTextRenderComponent* leftLog;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UMotionControllerComponent* rightController;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class USkeletalMeshComponent* rightHand;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UTextRenderComponent* rightLog;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UChildActorComponent* rightSword;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UChildActorComponent* leftSword;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UChildActorComponent* rightRemoteController;

		UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> leftSaberFactory;
		
		UPROPERTY(EditAnywhere)
			TSubclassOf<class AActor> rightSaberFactory;

		UPROPERTY(EditAnywhere)
			TSubclassOf<class AActor> rightRemoteControllerFactory;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerStat")
	float fullHp = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerStat")
	float currHp = 25;

public:
	UPROPERTY(EditAnywhere)
	float decreaseDelayTime = 0.5f;
	float currTime;

	int32 crashWallCount;
	bool bPlayerChk;

	UFUNCTION()
	void OnOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
		);

public:
	UPROPERTY(EditAnywhere, Category="MySettings|Inputs")
	class UInputMappingContext* imc_VRmap;

	UPROPERTY()
	class APlayerController* pc;

	UPROPERTY(EditAnywhere, Category="MySettings|Inputs")
	TArray<class UInputAction*> inputActions;

	void Scroll(const struct FInputActionValue& value);

	UFUNCTION(BlueprintImplementableEvent)
	void CallScrollUp();
	UFUNCTION(BlueprintImplementableEvent)
	void CallScrollDown();

	void ClickTrigger();

	UPROPERTY()
	class ASB_LaserPointer* laserPointer;

	void ReleaseTrigger();
};
