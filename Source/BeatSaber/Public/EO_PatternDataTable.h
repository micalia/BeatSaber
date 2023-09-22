#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EO_PatternDataTable.generated.h"


USTRUCT(BlueprintType)
struct FPatternDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float wEndms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int x2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int y2;
};

UCLASS()
class BEATSABER_API UEO_PatternDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
