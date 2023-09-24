#include "EO_EditorSongSlot.h"
#include <UMG/Public/Components/Button.h>
#include <UMG/Public/Blueprint/WidgetTree.h>
#include <UMG/Public/Components/TextBlock.h>
#include <Engine/StreamableManager.h>
#include <UMG/Public/Components/Image.h>

void UEO_EditorSongSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (btn_Slot != nullptr)
		btn_Slot->OnClicked.AddDynamic(this, &UEO_EditorSongSlot::SongSelectButtonClick);
}

void UEO_EditorSongSlot::SongSelectButtonClick()
{
	UEO_EditorWidget* widget = ReturnParentWidget();
	FStreamableManager assetLoader;
	
	UTexture2D* musicTexture = Cast<UTexture2D>(assetLoader.LoadSynchronous(FPaths::ConvertRelativePathToFull(imagePath)));
	widget->image_SongImage->SetBrushFromTexture(musicTexture);
	widget->text_Title->SetText(text_Title->GetText());
	widget->text_Artist->SetText(text_Artist->GetText());
	widget->text_BPM->SetText(text_BPM->GetText());
	widget->text_SongDuration->SetText(FText::AsNumber(songDuration));
	widget->SaveSelectedData(songPath, bpm);
}

class UEO_EditorWidget* UEO_EditorSongSlot::ReturnParentWidget()
{
	return Cast<UEO_EditorWidget>(GetParent()->GetParent()->GetOuter()->GetOuter());
}

