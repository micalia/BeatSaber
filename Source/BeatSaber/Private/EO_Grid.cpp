#include "EO_Grid.h"
#include <Components/BoxComponent.h>


AEO_Grid::AEO_Grid()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = boxComp;
	boxComp->SetBoxExtent(FVector(5, 300, 5));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Engine/BasicShapes/Cube.Cube'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeScale3D(FVector(0.1f, 6, 0.1f));
	}

	//gridController = Cast<AGridController>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridController::StaticClass()));
}

void AEO_Grid::BeginPlay()
{
	Super::BeginPlay();
	
	placedNotes.SetNum(4);
}

void AEO_Grid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

