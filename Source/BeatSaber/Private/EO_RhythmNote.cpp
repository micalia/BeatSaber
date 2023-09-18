#include "EO_RhythmNote.h"
#include <Components/BoxComponent.h>
#include "EO_Sync.h"
#include <Kismet/GameplayStatics.h>
#include <../Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponent/Public/ProceduralMeshComponent.h>
#include "EO_GridController.h"


AEO_RhythmNote::AEO_RhythmNote()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = boxComp;
	boxComp->SetBoxExtent(FVector(30));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/SB/Meshes/SM_BS_Cube.SM_BS_Cube'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0));
		meshComp->SetRelativeRotation(FRotator(0, 180, 180));
		meshComp->SetRelativeScale3D(FVector(0.33f));
		meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	}

	proceduralMeshComp = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Component"));
	proceduralMeshComp->SetupAttachment(RootComponent);
	proceduralMeshComp->SetRelativeLocation(FVector(0));
	proceduralMeshComp->SetRelativeRotation(FRotator(0, 0, 180));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> tempBlockMat(TEXT("'/Game/SB/Materials/M_Cube_Inst.M_Cube_Inst'"));
	if (tempBlockMat.Succeeded())
	{
		matInterface = tempBlockMat.Object;
	}

	sync = Cast<AEO_Sync>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_Sync::StaticClass()));
	gridController = Cast<AEO_GridController>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_GridController::StaticClass()));
}

void AEO_RhythmNote::BeginPlay()
{
	Super::BeginPlay();

	meshComp->SetMaterial(0, matInterface);
	cubeDynamicMaterial = UMaterialInstanceDynamic::Create(meshComp->GetMaterial(0), this);
	meshComp->SetMaterial(0, cubeDynamicMaterial);
	proceduralMeshComp->SetMaterial(0, cubeDynamicMaterial);

	SetNoteColor(0);


	syncPos = gridController->syncPos;
}

void AEO_RhythmNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PatternTest(DeltaTime);
	EditorSyncTest();
}

void AEO_RhythmNote::PatternTest(float deltaTime)
{
	if (sync != nullptr)
	{
		if (sync->isGenerate)
		{
			FVector p0 = GetActorLocation();
			FVector vt = FVector::BackwardVector * speed * deltaTime;
			FVector p = p0 + vt;
			SetActorLocation(p);

			if (GetActorLocation().X <= sync->GetActorLocation().X)
			{
				Destroy();
			}
		}
	}
}

void AEO_RhythmNote::EditorSyncTest()
{
	if (gridController != nullptr)
	{
		if (gridController->isPlaying)
		{
			if (GetActorLocation().X <= syncPos.X)
			{
				if (tik != nullptr && !isTik)
				{
					//UE_LOG(LogTemp, Warning, TEXT("one"));
					UGameplayStatics::PlaySound2D(GetWorld(), tik);
					isTik = true;
				}
			}
		}
		else
		{
			if (GetActorLocation().X >= syncPos.X)
			{
				isTik = false;
			}
			else
			{
				isTik = true;
			}
		}
	}
}

void AEO_RhythmNote::SetNoteColor(int num)
{
	colorIndex = num;

	switch (num)
	{
	case 0:
		cubeDynamicMaterial->SetScalarParameterValue(TEXT("ColorChoice"), 1);
		break;
	case 1:
		cubeDynamicMaterial->SetScalarParameterValue(TEXT("ColorChoice"), 0);
		break;
	}
}

void AEO_RhythmNote::SetNoteType(int num)
{
	typeIndex = num;
	cubeDynamicMaterial->SetScalarParameterValue(TEXT("TypeChoice"), num);
}

