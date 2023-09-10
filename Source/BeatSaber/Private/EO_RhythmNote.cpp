#include "EO_RhythmNote.h"
#include <Components/BoxComponent.h>
#include "EO_Sync.h"
#include <Kismet/GameplayStatics.h>


AEO_RhythmNote::AEO_RhythmNote()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = boxComp;
	boxComp->SetBoxExtent(FVector(50));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(boxComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Engine/BasicShapes/Cube.Cube'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	sync = Cast<AEO_Sync>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_Sync::StaticClass()));
}

void AEO_RhythmNote::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEO_RhythmNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (sync != nullptr)
	{
		if (sync->isGenerate)
		{
			FVector p0 = GetActorLocation();
			FVector vt = FVector::BackwardVector * speed * DeltaTime;
			FVector p = p0 + vt;
			SetActorLocation(p);

			if (GetActorLocation().X <= 0)
			{
				Destroy();
			}
		}
	}
}

