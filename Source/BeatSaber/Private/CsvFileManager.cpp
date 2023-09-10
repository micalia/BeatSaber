#include "CsvFileManager.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"

bool UCsvFileManager::SaveArrayText(FString saveDirectory, FString fileName, TArray<FString> saveText, bool allowOverWrite /*= false*/)
{
	saveDirectory += "\\";
	saveDirectory += fileName;

	if (!allowOverWrite)
	{
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*saveDirectory))
		{
			return false;
		}
	}

	FString finalString = "";
	for (FString& each : saveText)
	{
		finalString += each;
		finalString += LINE_TERMINATOR;
	}

	return FFileHelper::SaveStringToFile(finalString, *saveDirectory);
}
