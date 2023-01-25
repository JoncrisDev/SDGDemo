#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_PointOfInterestItem.generated.h"

class ACaptureTargetItem;

UCLASS()
class INTERVIEW_1_API UWidget_PointOfInterestItem : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void TargetMove_X(float NewXLocation) const;
	
	UFUNCTION(BlueprintCallable)
	void TargetMove_Y(float NewYLocation) const;
	
	UFUNCTION(BlueprintCallable)
	void TargetMove_Z(float NewZLocation) const;

	UFUNCTION(BlueprintCallable)
	void TargetRotate_Pitch(float NewXRotation) const;
	
	UFUNCTION(BlueprintCallable)
	void TargetRotate_Yaw(float NewYRotation) const;
	
	UFUNCTION(BlueprintCallable)
	void TargetRotate_Roll(float NewZRotation) const;

	UFUNCTION(BlueprintCallable)
	void TargetUpdateMaterial(int NewMaterialIdx) const;
	
	UFUNCTION(BlueprintCallable)
	void TargetChangeMesh(int NewMeshID) const;
	
protected:

	UPROPERTY(BlueprintReadWrite, Category = "DataSource", Meta = (ExposeOnSpawn=true))
	TObjectPtr<ACaptureTargetItem> CaptureTarget;
	
};
