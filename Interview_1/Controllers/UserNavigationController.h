#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UserNavigationController.generated.h"

/**
 * 
 */
UCLASS()
class INTERVIEW_1_API AUserNavigationController : public APlayerController
{
	GENERATED_BODY()

	virtual void SetupInputComponent() override;

	virtual void SpawnItemAtCursor();

	virtual void ChangeViewMode() const;
};
