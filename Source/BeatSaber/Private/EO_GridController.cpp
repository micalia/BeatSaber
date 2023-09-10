#include "EO_GridController.h"
#include <Components/AudioComponent.h>
#include "EO_Grid.h"
#include "EO_RhythmNote.h"
#include <Kismet/GameplayStatics.h>
#include "CsvFileManager.h"
#include <EngineUtils.h>
#include <Kismet/KismetMathLibrary.h>


AEO_GridController::AEO_GridController()
{
	PrimaryActorTick.bCanEverTick = true;

	audioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	RootComponent = audioComp;

	ConstructorHelpers::FClassFinder<AEO_Grid> gridTemp(TEXT("'/Game/EO/Blueprints/BP_Grid.BP_Grid_C'"));
	if (gridTemp.Succeeded())
	{
		gridFactory = gridTemp.Class;
	}

	ConstructorHelpers::FClassFinder<AActor> cursorTemp(TEXT("'/Game/EO/Blueprints/BP_CursorActor.BP_CursorActor_C'"));
	if (cursorTemp.Succeeded())
	{
		cursorFactory = cursorTemp.Class;
	}

	ConstructorHelpers::FClassFinder<AEO_RhythmNote> noteTemp(TEXT("'/Game/EO/Blueprints/BP_RhythmNote.BP_RhythmNote_C'"));
	if (noteTemp.Succeeded())
	{
		noteFactory = noteTemp.Class;
	}
}

void AEO_GridController::BeginPlay()
{
	Super::BeginPlay();
	
	musicBPM = 120.0f;
	frequeny = 44100.0f;

	sampleOffset = frequeny * offset;
	oneBeatTime = (60.0f / musicBPM);
	nextSample += sampleOffset;

	barPerSec = oneBeatTime * 4;

	audioComp->SetSound(testSound);

	MakeGrid();
}

void AEO_GridController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector worldLoc;
	FVector worldDir;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(worldLoc, worldDir);

	FHitResult hit;
	if (GetWorld()->LineTraceSingleByChannel(hit, worldLoc, worldLoc + worldDir * 1000000, ECollisionChannel::ECC_Visibility))
	{
		TArray<AActor*> ignoreActor;
		TArray<FHitResult> sphereHits;

		if (UKismetSystemLibrary::SphereTraceMulti(GetWorld(), hit.Location, hit.Location, 150, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false, ignoreActor, EDrawDebugTrace::None, sphereHits, true))
		{
			float min = 9999;
			
			for (FHitResult grid : sphereHits)
			{
				if (min > FVector::Distance(hit.Location, grid.GetActor()->GetActorLocation()))
				{
					float yPos = 0;

					min = FVector::Distance(hit.Location, grid.GetActor()->GetActorLocation());

					if (hit.Location.Y < -100)
					{
						yPos = -150;
						yArrIndex = 0;
					}
					else if (hit.Location.Y < 0)
					{
						yPos = -50;
						yArrIndex = 1;
					}
					else if (hit.Location.Y > 100)
					{
						yPos = 150;
						yArrIndex = 3;
					}
					else
					{
						yPos = 50;
						yArrIndex = 2;
					}
					tempNote->SetActorLocation(FVector(grid.GetActor()->GetActorLocation().X, yPos, 0));
					currentGrid = Cast<AEO_Grid>(grid.GetActor());

					UE_LOG(LogTemp, Warning, TEXT("%s"), *grid.GetActor()->GetName());
				}
			}
		}
	}

	if (isPlaying)
	{
		FVector p0 = GetActorLocation();
		FVector vt = FVector::BackwardVector * 500 * DeltaTime;
		FVector p = p0 + vt;
		SetActorLocation(p);
	}

	if (-(GetActorLocation().X / 500.0f) >= audioComp->GetSound()->GetDuration())
	{
		audioComp->Stop();
		isPlaying = false;
	}
}

void AEO_GridController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Scroll"), this, &AEO_GridController::MoveGrid);

	PlayerInputComponent->BindAction(TEXT("Click"), IE_Pressed, this, &AEO_GridController::PlacedNote);
	PlayerInputComponent->BindAction(TEXT("RemoveClick"), IE_Pressed, this, &AEO_GridController::RemoveNote);
	PlayerInputComponent->BindAction(TEXT("SoundPlay"), IE_Pressed, this, &AEO_GridController::SoundPlay);
	PlayerInputComponent->BindAction(TEXT("TestKey"), IE_Pressed, this, &AEO_GridController::OutData);
}

void AEO_GridController::MakeGrid()
{
	for (int i = 0; i < audioComp->GetSound()->GetDuration() * 1000 + oneBeatTime * 1000;)
	{
		AEO_Grid* gridTemp = GetWorld()->SpawnActor<AEO_Grid>(gridFactory, FVector(500 * (i * 0.001f), 0, 0), FRotator());
		gridTemp->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		i += oneBeatTime * 1000;
	}

	tempNote = GetWorld()->SpawnActor<AActor>(cursorFactory, FVector(0, 0, 0), FRotator());
}

void AEO_GridController::MoveGrid(float value)
{
	if (!isPlaying)
	{
		if (value >= 1)
		{
			if (GetActorLocation().X < offset)
			{
				SetActorLocation(GetActorLocation() + FVector(500 * (oneBeatTime * 1000 * 0.001f), 0, 0));
			}
			else
			{
				SetActorLocation(FVector(offset, 0, 0));
			}
		}
		else if (value <= -1)
		{
			if (GetActorLocation().X > -(audioComp->GetSound()->GetDuration() * 500))
			{
				SetActorLocation(GetActorLocation() - FVector(500 * (oneBeatTime * 1000 * 0.001f), 0, 0));
			}
			else
			{
				SetActorLocation(FVector(-(audioComp->GetSound()->GetDuration() * 500), 0, 0));
			}
		}
	}
}

void AEO_GridController::PlacedNote()
{
	if (currentGrid->placedNotes[yArrIndex] == nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AEO_RhythmNote* noteTemp = GetWorld()->SpawnActor<AEO_RhythmNote>(noteFactory, tempNote->GetTransform(), param);
		noteTemp->AttachToActor(currentGrid, FAttachmentTransformRules::KeepWorldTransform);
		noteTemp->myPos = yArrIndex;
		currentGrid->placedNotes[yArrIndex] = noteTemp;
	}
}

void AEO_GridController::RemoveNote()
{
	if (currentGrid != nullptr)
	{
		if (currentGrid->placedNotes[yArrIndex] != nullptr)
		{
			AEO_RhythmNote* noteTemp = currentGrid->placedNotes[yArrIndex];

			currentGrid->placedNotes[yArrIndex] = nullptr;
			noteTemp->Destroy();
		}
	}
}

void AEO_GridController::SoundPlay()
{
	if (!audioComp->IsPlaying())
	{
		if (-(GetActorLocation().X / 500.0f) >= audioComp->GetSound()->GetDuration())
			SetActorLocation(FVector(0));

		audioComp->Play(-(GetActorLocation().X / 500.0f));
		isPlaying = true;
	}
	else
	{
		if (isPlaying == false)
		{
			audioComp->SetPaused(false);
			isPlaying = true;
		}
		else
		{
			audioComp->SetPaused(true);
			isPlaying = false;
		}
	}
}

void AEO_GridController::OutData()
{
	int i = 0;

	SetActorLocation(FVector(0));

	TArray<FString> data;
	data.Add(TEXT(",ms,x,y,color,rot"));

	for (AEO_RhythmNote* noteData : TActorRange<AEO_RhythmNote>(GetWorld()))
	{
		FString textData;

		textData += FString::FromInt(i);
		textData += ",";
		//ms
		textData += FString::FromInt(UKismetMathLibrary::FFloor(noteData->GetActorLocation().X * 1000 / 500));
		textData += ",";
		//x position
		textData += "2";
		textData += ",";
		//y position
		textData += FString::FromInt(noteData->myPos);
		textData += ",";
		//color
		textData += "0";
		textData += ",";
		//rotation
		textData += "0";

		data.Add(textData);

		i++;
	}

	UCsvFileManager::SaveArrayText(UKismetSystemLibrary::GetProjectDirectory(), TEXT("test.csv"), data);
	UE_LOG(LogTemp, Warning, TEXT("CSV make complete"));
}

