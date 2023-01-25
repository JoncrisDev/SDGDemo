#include "CaptureManagerComponent.h"
#include "Interview_1/Cameras/CaptureCamera.h"
#include "Interview_1/GM/Interview_1GameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCaptureManagerComponent::UCaptureManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UCaptureManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Acquire the first capture camera
	TArray<AActor *> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACaptureCamera::StaticClass(), OutActors);
	if (ACaptureCamera* CaptureCam = Cast<ACaptureCamera>(OutActors.Top()))
	{
		CaptureCamera = CaptureCam;
	}
	
}

void UCaptureManagerComponent::StartCapture() 
{
	if(const AInterview_1GameMode * GM = GetWorld()->GetAuthGameMode<AInterview_1GameMode>())
	{
		for (auto const Target : GM->CapturePoints)
		{
			if (auto const CaptureTarget = Cast<ACaptureTargetItem>(Target))
			{
				if(CaptureTarget->GetWantsPanorama())
				{
					CaptureCamera->ItemsToPanorama.Emplace(CaptureTarget);
				}
			}
		}
		FramesToCapture = CaptureCamera->ItemsToPanorama.Num() * CaptureCamera->PanoramaFrames;
		if (GM->bRandomSample)
		{
			FramesToCapture += GM->RandomSamplesToCapture;
		}
		
	}


	CaptureCamera->StartCapture();
}

void UCaptureManagerComponent::StopCapture()
{
	CaptureCamera->StopCapture();
}


// Called every frame
void UCaptureManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

