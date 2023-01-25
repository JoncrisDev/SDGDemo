#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "UserNavigationCamera.generated.h"

UCLASS()
class INTERVIEW_1_API AUserNavigationCamera : public ADefaultPawn
{
	GENERATED_BODY()

	AUserNavigationCamera();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> ViewCamera;


public:
	FORCEINLINE class UCameraComponent* GetViewCamera() const { return ViewCamera; }
};
