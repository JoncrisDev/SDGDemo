#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interview_1/Interfaces/PointOfInterest.h"
#include "CaptureTargetItem.generated.h"

// Convenience helper for Material selection
UENUM(BlueprintType)
enum class ItemMaterials : uint8
{
	Default,
	Camo,
	Dark
};

UCLASS()
class INTERVIEW_1_API ACaptureTargetItem : public AActor, public IPointOfInterest
{
	GENERATED_BODY()


	// Physical representation of the object in the world
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	// Attach point for Capture Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	// Interface Implementation
	// @todo: oh dear, oh dear this interface is not properly utilised.
	virtual void CapturePanorama() const override;
	
	// Should we panorama capture this target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture Settings", meta = (AllowPrivateAccess = "true"))
	bool bWantsPanorama;
	
public:
	
	ACaptureTargetItem();

	bool bPanoramaDone;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture Settings")
	int NumFramesToPanorama;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture Settings")
	bool bCapturing;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture Settings")
	int PanoramaCapturedSoFar;

	UFUNCTION(BlueprintCallable)
	virtual void ChangeMaterial(int MaterialIdx);

	UFUNCTION(BlueprintCallable)
	void SetWantsPanorama(bool bPanorama);

	UFUNCTION(BlueprintCallable)
	bool GetWantsPanorama() const;
	

	// Mesh Materials
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	TObjectPtr<UMaterialInterface> DefaultMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	TObjectPtr<UMaterialInterface> CamoMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	TObjectPtr<UMaterialInterface> DarkMaterial;

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
	
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }

};
