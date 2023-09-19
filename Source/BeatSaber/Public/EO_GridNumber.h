#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EO_GridNumber.generated.h"

UCLASS()
class BEATSABER_API UEO_GridNumber : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* text_GridNum;

public:
	void SetGridNumber(int num);
};
