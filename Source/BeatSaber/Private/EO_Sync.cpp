#include "EO_Sync.h"
#include <Components/AudioComponent.h>
#include <Engine/DataTable.h>
#include "EO_RhythmNote.h"
#include "EO_PatternDataTable.h"


AEO_Sync::AEO_Sync()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AEO_RhythmNote> noteTemp(TEXT("'/Game/EO/Blueprints/BP_RhythmNote.BP_RhythmNote_C'"));
	if (noteTemp.Succeeded())
	{
		noteFactory = noteTemp.Class;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> patternTemp(TEXT("'/Game/EO/Resources/test.test'"));
	if (patternTemp.Succeeded())
	{
		patternData = patternTemp.Object;
	}

	audioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	audioComp->SetupAttachment(RootComponent);
}

void AEO_Sync::BeginPlay()
{
	Super::BeginPlay();
	
	musicBPM = 120.0f;
	frequeny = 44100.0f;

	sampleOffset = frequeny * offset;
	oneBeatTime = (60.0f / musicBPM);
	nextSample += sampleOffset;

	barPerSec = oneBeatTime * 4;

	audioComp->SetSound(testSound);

	startPos = 500 * 3;

	GenerateNote();

	if (isGenerate)
	{
		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, this, &AEO_Sync::MusicPlay, 3.0f, false);
	}
}

void AEO_Sync::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEO_Sync::MusicPlay()
{
	audioComp->Play();
}

void AEO_Sync::GenerateNote()
{
	if (patternData != nullptr)
	{
		for (int i = 0; i < patternData->GetRowNames().Num(); i++)
		{
			FPatternDataTableRow* row = patternData->FindRow<FPatternDataTableRow>(FName(*(FString::FormatAsNumber(i))), FString(""));

			GetWorld()->SpawnActor<AEO_RhythmNote>(noteFactory, FVector(startPos + offset + 500 * (row->ms * 0.001f), YGeneratePos(row->y), XGeneratePos(row->x)), FRotator());
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("All Generated"));
	isGenerate = true;
}

float AEO_Sync::XGeneratePos(int rowX)
{
	if (rowX == 0)
	{
		return 0;
	}
	else if (rowX == 1)
	{
		return 1;
	}
	else if (rowX == 2)
	{
		return 2;
	}

	return -1;
}

float AEO_Sync::YGeneratePos(int rowY)
{
	if (rowY == 0)
	{
		return -150;
	}
	else if (rowY == 1)
	{
		return -50;
	}
	else if (rowY == 2)
	{
		return 50;
	}
	else if (rowY == 3)
	{
		return 150;
	}

	return -1;
}

