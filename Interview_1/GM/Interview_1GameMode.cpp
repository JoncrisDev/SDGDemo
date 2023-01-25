#include "Interview_1GameMode.h"
#include "Interview_1/Actors/CaptureTargetItem.h"
#include "Interview_1/Interfaces/PointOfInterest.h"
#include "Interview_1/Cameras/CaptureCamera.h"
#include "Interview_1/Components/CaptureManagerComponent.h"
#include "Interview_1/Components/EnvironmentManagerComponent.h"
#include "Interview_1/Controllers/UserNavigationController.h"
#include "Kismet/GameplayStatics.h"


AInterview_1GameMode::AInterview_1GameMode()
{
	DefaultPawnClass = ACaptureCamera::StaticClass();
	PlayerControllerClass = AUserNavigationController::StaticClass();
	
	EnvironmentManager = CreateDefaultSubobject<UEnvironmentManagerComponent>(TEXT("EnvironmentManager"));
	CaptureManager = CreateDefaultSubobject<UCaptureManagerComponent>(TEXT("CaptureManager"));
	
	// Some Capture config Defaults
	Config = {true, 1920, 1080, PNG, 100};
}

void AInterview_1GameMode::SpawnNewCaptureTargetItem() 
{
	if (const APlayerController * PC = GetWorld()->GetFirstPlayerController())
	{
		const FVector OurLocation = PC->GetPawn()->GetActorLocation();
		const FRotator OurViewRotation = PC->GetPawn()->GetViewRotation();

		// push the actor default spawn point just in front of the players viewpoint 
		const FVector TraceStartLocation = OurLocation + (OurViewRotation.Vector() * 2000.0f);
		
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStartLocation, OurLocation - FVector(0.0f, 0.0f, 5000.0f), ECC_Visibility);
		if (HitResult.bBlockingHit && IsValid(CaptureTargetToSpawn))
		{
			auto const NewCapturePoint = GetWorld()->SpawnActor<AActor>(CaptureTargetToSpawn, HitResult.Location, FRotator(0.0f, 0.0f, 0.0f));
			CapturePoints.Push(NewCapturePoint);
			
		}
	}
}

void AInterview_1GameMode::SpawnNewCaptureTargetItemAtCursor() 
{
	if (const APlayerController * PC = GetWorld()->GetFirstPlayerController())
	{
		FHitResult HitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility, false ,HitResult);

		// @note: for demo purposes we are making the hopeful assumption that the user has placed the cursor over the terrain not somewhere silly.
		if (HitResult.bBlockingHit && IsValid(CaptureTargetToSpawn))
		{
			auto const NewCapturePoint = GetWorld()->SpawnActor<AActor>(CaptureTargetToSpawn, HitResult.Location, FRotator(0.0f, 0.0f, 0.0f));
			CapturePoints.Push(NewCapturePoint);
			
		}
	}
}

// todo
void AInterview_1GameMode::SpawnNewCaptureTargetsInBox(const int NumTargetsToSpawn, const int BoxExtent)
{
	if (const APlayerController * PC = GetWorld()->GetFirstPlayerController())
	{
		const FVector OurLocation = PC->GetPawn()->GetActorLocation();
		const FRotator OurViewRotation = PC->GetPawn()->GetViewRotation();

		// push the actor default spawn point just in front of the players viewpoint 
		const FVector TraceStartLocation = OurLocation + (OurViewRotation.Vector() * 2000.0f);
		
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStartLocation, OurLocation - FVector(0.0f, 0.0f, 5000.0f), ECC_Visibility);
	}
}

void AInterview_1GameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor *> OutActors;
	UGameplayStatics::GetAllActorsWithInterface(this, UPointOfInterest::StaticClass(), OutActors);
	CapturePoints.Reserve(OutActors.Num());
	for (auto const POI : OutActors)
	{
		CapturePoints.Emplace(POI);
	}
}

void AInterview_1GameMode::SetCaptureConfig(FCaptureConfig NewConfig)
{
	Config = NewConfig;
}

FCaptureConfig & AInterview_1GameMode::GetCaptureConfig() 
{
	return Config;
}

void AInterview_1GameMode::StartCapture() 
{
	GetCapturePoints();
	bIsCapturing = true;
	CaptureManager->StartCapture();
}

void AInterview_1GameMode::StopCapture()
{
	bIsCapturing = true;
	CaptureManager->StopCapture();
}

void AInterview_1GameMode::GetCapturePoints() 
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACaptureTargetItem::StaticClass(),CapturePoints);
}

void AInterview_1GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


