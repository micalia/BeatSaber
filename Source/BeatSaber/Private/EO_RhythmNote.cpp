#include "EO_RhythmNote.h"
#include <Components/BoxComponent.h>
#include "EO_Sync.h"
#include <Kismet/GameplayStatics.h>
#include <../Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponent/Public/ProceduralMeshComponent.h>


AEO_RhythmNote::AEO_RhythmNote()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = boxComp;
	boxComp->SetBoxExtent(FVector(50));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/RedNoteBlock.RedNoteBlock'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0,0,-50));
		meshComp->SetRelativeRotation(FRotator(0,90,0));
		meshComp->SetRelativeScale3D(FVector(0.5f));
		meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	}

	proceduralMeshComp = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Component"));
	proceduralMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> tempBlockMat(TEXT("'/Game/SB/Materials/M_Cube_Inst.M_Cube_Inst'"));
	if (tempBlockMat.Succeeded())
	{
		matInterface = tempBlockMat.Object;
	}

	sync = Cast<AEO_Sync>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_Sync::StaticClass()));
}

void AEO_RhythmNote::BeginPlay()
{
	Super::BeginPlay();
	
	meshComp->SetMaterial(0, matInterface);
	cubeDynamicMaterial = UMaterialInstanceDynamic::Create(meshComp->GetMaterial(0), this);
	meshComp->SetMaterial(0, cubeDynamicMaterial);
	proceduralMeshComp->SetMaterial(0, cubeDynamicMaterial);

	SetNoteColor(0);
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

			if (GetActorLocation().X <= sync->GetActorLocation().X)
			{
				Destroy();
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

