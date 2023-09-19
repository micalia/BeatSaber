#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EO_SongDataTable.generated.h"

USTRUCT(BlueprintType)
struct FSongDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString songName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString artist;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float songDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float bpm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString imagePath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString songPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float previewSongTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString patternPath;
};

UCLASS()
class BEATSABER_API UEO_SongDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
