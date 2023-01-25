#include "UserNavigationController.h"

#include "Interview_1/Cameras/UserNavigationCamera.h"
#include "Interview_1/GM/Interview_1GameMode.h"

void AUserNavigationController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// @todo: move any bound actions over to UE5 enhanced input.
	InputComponent->BindAction("SpawnItemAtCursor", EInputEvent::IE_Pressed, this, &AUserNavigationController::SpawnItemAtCursor);
}

void AUserNavigationController::SpawnItemAtCursor() 
{
	if(auto GM = GetWorld()->GetAuthGameMode<AInterview_1GameMode>())
	{
		GM->SpawnNewCaptureTargetItemAtCursor();
	}
}

void AUserNavigationController::ChangeViewMode() const
{
	if (const AUserNavigationCamera* TheUser = Cast<AUserNavigationCamera>(GetPawn()))
	{
		// TheUser->GetViewCamera()->AddOrUpdateBlendable();
		
	}
}
