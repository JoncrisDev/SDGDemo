#include "CaptureTargetItem.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interview_1/Interview_1.h"


ACaptureTargetItem::ACaptureTargetItem()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->SetupAttachment(RootComponent);

	bWantsPanorama = true;
	
}

// From the interface
void ACaptureTargetItem::CapturePanorama() const
{
}

void ACaptureTargetItem::ChangeMaterial(int MaterialIdx) 
{
	UE_LOG(LogGameplay, Log, TEXT("Changing to material ID: %d"), MaterialIdx)
	
	switch (MaterialIdx)
	{
		case ItemMaterials::Default: {
			UE_LOG(LogGameplay, Log, TEXT("%s =  %s"), *GetName(), TEXT("Default"))
				Mesh->SetMaterial(0, DefaultMaterial);
				break;
		}

		case ItemMaterials::Camo: {
			UE_LOG(LogGameplay, Log, TEXT("%s =  %s"), *GetName(), TEXT("Camo"))
				Mesh->SetMaterial(0, CamoMaterial);
				break;
		}

		case ItemMaterials::Dark: {
			UE_LOG(LogGameplay, Log, TEXT("%s =  %s"), *GetName(), TEXT("Dark"))
				Mesh->SetMaterial(0, DarkMaterial);
				break;
		}
		
		default: {
				
		}
	}
}

void ACaptureTargetItem::SetWantsPanorama(bool bPanorama)
{
	bWantsPanorama = bPanorama;
}

bool ACaptureTargetItem::GetWantsPanorama() const
{
	return bWantsPanorama;
}

void ACaptureTargetItem::BeginPlay()
{
	Super::BeginPlay();
}

void ACaptureTargetItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

