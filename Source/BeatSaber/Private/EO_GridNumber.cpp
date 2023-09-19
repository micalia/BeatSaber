#include "EO_GridNumber.h"
#include <UMG/Public/Components/TextBlock.h>

void UEO_GridNumber::SetGridNumber(int num)
{
	text_GridNum->SetText(FText::AsNumber(num));
}
