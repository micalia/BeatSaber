#include "EO_EditorWidget.h"
#include <UMG/Public/Components/ScrollBox.h>
#include <UMG/Public/Components/TextBlock.h>
#include <Engine/StreamableManager.h>
#include <Components/AudioComponent.h>
#include <UMG/Public/Components/WidgetSwitcher.h>

UEO_EditorWidget::UEO_EditorWidget(const FObjectInitializer& Object) : Super(Object)
{
	ConstructorHelpers::FClassFinder<UEO_EditorSongSlot> slotTemp(TEXT("'/Game/EO/Blueprints/BP_EditorSongSlot.BP_EditorSongSlot_C'"));
	if (slotTemp.Succeeded())
	{
		songSlot = slotTemp.Class;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> songTemp(TEXT("'/Game/EO/SongData.SongData'"));
	if (songTemp.Succeeded())
	{
		songDatatable = songTemp.Object;
	}

	ConstructorHelpers::FClassFinder<AEO_GridController> gControllerTemp(TEXT("'/Game/EO/Blueprints/BP_GridController.BP_GridController_C'"));
	if (gControllerTemp.Succeeded())
	{
		gridControllerFactory = gControllerTemp.Class;
	}
}

void UEO_EditorWidget::NativeConstruct()
{
	if (btn_Add != nullptr)
		btn_Add->OnClicked.AddDynamic(this, &UEO_EditorWidget::AddPattern);

	GenerateList();
}

void UEO_EditorWidget::GenerateList()
{
	if (songDatatable != nullptr)
	{
		for (int i = 0; i < songDatatable->GetRowNames().Num(); i++)
		{
			FSongDataTableRow* row = songDatatable->FindRow<FSongDataTableRow>(FName(*(FString::FormatAsNumber(i))), FString(""));

			UEO_EditorSongSlot* songSlotTemp = CreateWidget<UEO_EditorSongSlot>(GetWorld(), songSlot);
			songSlotTemp->text_Title->SetText(FText::FromString(row->songName));
			songSlotTemp->text_Artist->SetText(FText::FromString(row->artist));
			songSlotTemp->text_BPM->SetText(FText::AsNumber(row->bpm));

			songSlotTemp->bpm = row->bpm;
			songSlotTemp->songDuration = row->songDuration;
			songSlotTemp->offset = row->offset;

			songSlotTemp->imagePath = row->imagePath;
			songSlotTemp->songPath = row->songPath;

			scroll_SongList->AddChild(songSlotTemp);
		}
	}
}

void UEO_EditorWidget::AddPattern()
{
	if (selectSongPath != "none")
	{
		UE_LOG(LogTemp, Warning, TEXT("clicked"));
		FStreamableManager assetLoader;

		gridController = GetWorld()->SpawnActor<AEO_GridController>(gridControllerFactory, FVector(), FRotator());

		USoundBase* music = Cast<USoundBase>(assetLoader.LoadSynchronous(FPaths::ConvertRelativePathToFull(selectSongPath)));
		gridController->audioComp->SetSound(music);
		gridController->musicBPM = selectBPM;
		gridController->offset = selectOffset;
		gridController->MakeGrid();

		ws_Switcher->SetActiveWidgetIndex(1);

		if (btn_Play != nullptr)
			btn_Play->OnClicked.AddDynamic(this, &UEO_EditorWidget::SoundPlay);
		if (btn_RedNote != nullptr)
			btn_RedNote->OnClicked.AddDynamic(this, &UEO_EditorWidget::ChangeRedNote);
		if (btn_BlueNote != nullptr)
			btn_BlueNote->OnClicked.AddDynamic(this, &UEO_EditorWidget::ChangeBlueNote);
		if (btn_Bomb != nullptr)
			btn_Bomb->OnClicked.AddDynamic(this, &UEO_EditorWidget::ChangeBomb);
		if (btn_Wall != nullptr)
			btn_Wall->OnClicked.AddDynamic(this, &UEO_EditorWidget::ChangeWall);
	}
}

void UEO_EditorWidget::SoundPlay()
{
	if (gridController != nullptr)
		gridController->SoundPlay();
}

void UEO_EditorWidget::ChangeRedNote()
{
	if (gridController != nullptr)
		gridController->ChangeRedColor();
}

void UEO_EditorWidget::ChangeBlueNote()
{
	if (gridController != nullptr)
		gridController->ChangeBlueColor();
}

void UEO_EditorWidget::ChangeBomb()
{
	if (gridController != nullptr)
		gridController->ChangeBomb();
}

void UEO_EditorWidget::ChangeWall()
{
	if (gridController != nullptr)
		gridController->ChangeWall();
}

void UEO_EditorWidget::SaveSelectedData(FString songPath, float BPM, float offset)
{
	selectSongPath = songPath;
	selectBPM = BPM;
	selectOffset = offset;
}

