#include "CaptureCamera.h"
#include "Interview_1/Interview_1.h"
#include "Interview_1/GM/Interview_1GameMode.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"
#include "ImageUtils.h"
#include "UnrealClient.h"
#include "EntitySystem/MovieSceneCachedEntityFilterResult.h"
#include "Field/FieldSystemNoiseAlgo.h"

ACaptureCamera::ACaptureCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Camera"));
	RootComponent = Camera;
	Camera->bCaptureOnMovement = false;
	Camera->bCaptureEveryFrame = false;
	// Camera->SetupAttachment(RootComponent);

	PanoramaFrames = 18;
}

void ACaptureCamera::StartCapture()
{
	bIsCapturing = true;
}

void ACaptureCamera::StopCapture()
{
	ItemsToPanorama.Empty();
	bIsCapturing = false;
}

void ACaptureCamera::BeginPlay()
{
	Super::BeginPlay();
}

void ACaptureCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(AInterview_1GameMode* GM = GetWorld()->GetAuthGameMode<AInterview_1GameMode>())
	{
		if (bIsCapturing)
		{
			if (ItemsToPanorama.Num() > 0)
			{
				if(!ItemsToPanorama.Top()->bPanoramaDone)
				{
					CapturePanoramaItem(ItemsToPanorama.Top());
				}
				else
				{
					ItemsToPanorama.Pop();
				}
			}
			else if (GM->bRandomSample && RandomSamples < GM->RandomSamplesToCapture)
			{
				// Testing to remove
				CaptureRandomSample();
				RandomSamples++;
			}	
			else
			{
				GM->bIsCapturing = false;
				GM->FramesCaptured = 0;
				bIsCapturing = false;
			}
		}
	}
}

// Take a turn table capture of a given target
void ACaptureCamera::CapturePanoramaItem(ACaptureTargetItem* Target) 
{
	// @todo: I should be able to remove bWantsPanorama here.
	if (Target->GetWantsPanorama() && !Target->bPanoramaDone)
	{
		if (!Target->bCapturing)
		{
			AttachToComponent(Target->GetSpringArm(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Target->bCapturing = true;
		}
		else
		{
			// @note: Collision detection is disabled by default
			constexpr float RotationStep = 20.0f;
			Target->GetSpringArm()->AddRelativeRotation(FRotator(0.0f, RotationStep, 0.0f));

			Capture(FString::Printf(TEXT("%s_panorama"), *Target->GetName()));
			PanoramaFramesDone++;
			if (PanoramaFramesDone >= PanoramaFrames)
			{
				Target->bPanoramaDone = true;
				Target->bCapturing = false;
				PanoramaFramesDone = 0;
			}
		}
		
	}
}

void ACaptureCamera::CaptureRandomSample() 
{
	// @todo: 
	// perform a ground trace to maintain a sensible distance from the ground.
	// i.e we do not want capture underneath the landscape actor.

	if (const auto * GM = GetWorld()->GetAuthGameMode<AInterview_1GameMode>())
	{
		const float BoxHalf = GM->RandomSampleRange / 2.0f;
		const FVector SampleStart = GM->RandomSampleStartLocation; 
		
		const float Desired_X = FMath::RandRange(SampleStart.X - BoxHalf, SampleStart.X + BoxHalf);
		const float Desired_Y = FMath::RandRange(SampleStart.Y - BoxHalf, SampleStart.Y + BoxHalf);
		const float Desired_Z = FMath::RandRange(SampleStart.Z - BoxHalf, SampleStart.Z + BoxHalf);
		
		SetActorLocation(FVector(Desired_X, Desired_Y, Desired_Z));

		// This is random ? but ignores gimbal role over?
		const FRotator RandomRotation(FMath::RandRange(0, 360), FMath::RandRange(0, 360), FMath::RandRange(0, 380));
		SetActorRotation(RandomRotation);
		
		Capture(TEXT("Random_Sample"));
		
	}
	
	
}

// Perform the capture
void ACaptureCamera::Capture(FString FileLabel) const
{
	if (AInterview_1GameMode * GM = GetWorld()->GetAuthGameMode<AInterview_1GameMode>())
	{
		const int ResX = GM->GetCaptureConfig().Resolution_X;
		const int ResY = GM->GetCaptureConfig().Resolution_Y;
		
		TArray<FColor> ColorData;
		UTextureRenderTarget2D * TextureRenderTarget = NewObject<UTextureRenderTarget2D>();
		TextureRenderTarget->InitCustomFormat(ResX,ResY,PF_B8G8R8A8,false);
		Camera->TextureTarget = TextureRenderTarget;

		Camera->CaptureScene();
		
		ColorData.Empty();
		ColorData.Reserve(ResX * ResY);

		// waits for the rendering thread to finish executing all pending instructions
		TextureRenderTarget->GameThread_GetRenderTargetResource()->ReadPixels(ColorData);
		ColorData.Shrink();

		const FString Filepath = FPaths::ProjectDir() / TEXT("Snapshots") / FileLabel / FString::Printf(TEXT("capture_%d%s"), GM->FramesCaptured, TEXT(".bmp"));
		FFileHelper::CreateBitmap(*Filepath, ResX, ResY, ColorData.GetData());
		

		GM->FramesCaptured++;
	}
}

