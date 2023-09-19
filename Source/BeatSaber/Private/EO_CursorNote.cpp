#include "EO_CursorNote.h"
#include <../Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponent/Public/ProceduralMeshComponent.h>


AEO_CursorNote::AEO_CursorNote()
{
	PrimaryActorTick.bCanEverTick = true;

	rootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root scene component"));
	RootComponent = rootSceneComp;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/SB/Meshes/SM_BS_Cube.SM_BS_Cube'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0));
		meshComp->SetRelativeRotation(FRotator(0,180,180));
		meshComp->SetRelativeScale3D(FVector(0.33f));
		meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	}

	proceduralMeshComp = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Component"));
	proceduralMeshComp->SetupAttachment(RootComponent);
	proceduralMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	proceduralMeshComp->SetRelativeLocation(FVector(0));
	proceduralMeshComp->SetRelativeRotation(FRotator(0,0,180));

	bombMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bomb Mesh Component"));
	bombMeshComp->SetupAttachment(RootComponent);
	bombMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> bombMeshTemp(TEXT("'/Game/SB/Models/SphereObstacle/Bomb.Bomb'"));
	if (bombMeshTemp.Succeeded())
	{
		bombMeshComp->SetStaticMesh(bombMeshTemp.Object);
	}
	bombMeshComp->SetVisibility(false);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> tempBlockMat(TEXT("'/Game/SB/Materials/M_Cube_Inst.M_Cube_Inst'"));
	if (tempBlockMat.Succeeded())
	{
		matInterface = tempBlockMat.Object;
	}
}

void AEO_CursorNote::BeginPlay()
{
	Super::BeginPlay();
	
	meshComp->SetMaterial(0, matInterface);
	cubeDynamicMaterial = UMaterialInstanceDynamic::Create(meshComp->GetMaterial(0), this);
	meshComp->SetMaterial(0, cubeDynamicMaterial);
	proceduralMeshComp->SetMaterial(0, cubeDynamicMaterial);

	SwitchNote(0);
	SwitchNoteType(1); 
}

void AEO_CursorNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEO_CursorNote::SwitchNote(int num)
{
	switch (num)
	{
	case 0:
		meshComp->SetVisibility(true);
		bombMeshComp->SetVisibility(false);
		cubeDynamicMaterial->SetScalarParameterValue(TEXT("ColorChoice"), 1);
		break;
	case 1:
		meshComp->SetVisibility(true);
		bombMeshComp->SetVisibility(false);
		cubeDynamicMaterial->SetScalarParameterValue(TEXT("ColorChoice"), 0);
		break;
	case 2:
		bombMeshComp->SetVisibility(true);
		meshComp->SetVisibility(false);
		break;
	}
}

void AEO_CursorNote::SwitchNoteType(int num)
{
	switch (num)
	{
	case 0:
		cubeDynamicMaterial->SetScalarParameterValue(TEXT("TypeChoice"), 0);
		break;
	case 1:
		cubeDynamicMaterial->SetScalarParameterValue(TEXT("TypeChoice"), 1);
		break;
	}
}

