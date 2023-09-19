#include "EO_Grid.h"
#include <Components/BoxComponent.h>
#include <UMG/Public/Components/WidgetComponent.h>
#include "EO_GridNumber.h"


AEO_Grid::AEO_Grid()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = boxComp;
	boxComp->SetBoxExtent(FVector(5, 300, 5));
	boxComp->SetCollisionProfileName(TEXT("Grid"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Engine/BasicShapes/Cube.Cube'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeScale3D(FVector(0.1f, 6, 0.1f));
	}

	widgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	widgetComp->SetupAttachment(RootComponent);
	widgetComp->SetCollisionProfileName(TEXT("NoCollision"));
	ConstructorHelpers::FClassFinder<UUserWidget> gridNumTemp(TEXT("'/Game/EO/Blueprints/UI_GridNumber.UI_GridNumber_C'"));
	if (gridNumTemp.Succeeded())
	{
		gridNumWidget = gridNumTemp.Class;
		widgetComp->SetWidgetClass(gridNumWidget);
		widgetComp->SetRelativeLocationAndRotation(FVector(0, 580, 0), FRotator(90, 0, 180));
	}
	widgetComp->SetVisibility(false);
}

void AEO_Grid::BeginPlay()
{
	Super::BeginPlay();

}

void AEO_Grid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEO_Grid::SetActive(bool bCheck)
{
	meshComp->SetVisibility(bCheck);

	if (bCheck)
	{
		boxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		boxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AEO_Grid::SetGridNumber(int num)
{
	Cast<UEO_GridNumber>(widgetComp->GetWidget())->SetGridNumber(num);
	widgetComp->SetVisibility(true);
}

