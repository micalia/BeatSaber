#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CsvFileManager.generated.h"


UCLASS()
class BEATSABER_API UCsvFileManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static bool SaveArrayText(FString saveDirectory, FString fileName, TArray<FString> saveText, bool allowOverWrite = false);
};
