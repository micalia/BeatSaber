// Fill out your copyright notice in the Description page of Project Settings.


#include "SongListUI.h"
#include <UMG/Public/Components/ScrollBox.h>
#include <Kismet/KismetMathLibrary.h>
#include "Blueprint/WidgetLayoutLibrary.h"
#include <UMG/Public/Components/CanvasPanelSlot.h>

void USongListUI::ScrollDown()
{ 
	if (SongList) {
			
			scrollVal += 10;
			if (scrollVal > SongList->GetScrollOffsetOfEnd()) {
				scrollVal = SongList->GetScrollOffsetOfEnd();
				return;
			}
			SongList->SetScrollOffset(scrollVal);
	}
} 

void USongListUI::ScrollUp()
{
	if (SongList) {
		scrollVal -= 10;
		if (scrollVal < 0) {
			scrollVal = 0;
			return;
		}

		SongList->SetScrollOffset(scrollVal);

	}
}
