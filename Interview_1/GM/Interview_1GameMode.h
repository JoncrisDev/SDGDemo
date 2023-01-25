// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interview_1/Actors/CaptureTargetItem.h"
#include "Interview_1/Interfaces/PointOfInterest.h"
#include "Interview_1GameMode.generated.h"

// class UEnvironmentLightManagerComponent;

// capture output format
UENUM(BlueprintType)
enum FILE_FORMAT : int {
	PNG    UMETA(DisplayName = "PNG"),
	BMP    UMETA(DisplayName = "BMP"),
};

// Holds capture config presets.
USTRUCT(BlueprintType)
struct FCaptureConfig
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCaptureTurntablePOI;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Resolution_X;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Resolution_Y;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<FILE_FORMAT> FileFormat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int FramesToCapture;
};

UCLASS(minimalapi)
class AInterview_1GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UEnvironmentManagerComponent* EnvironmentManager;
	
	UFUNCTION(BlueprintCallable)
	UEnvironmentManagerComponent* GetEnvironmentManager() const { return EnvironmentManager; }
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCaptureManagerComponent* CaptureManager;

	UFUNCTION(BlueprintCallable)
	UCaptureManagerComponent* GetCaptureManager() const { return CaptureManager; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CaptureTarget", meta = (AllowPrivateAccess = "true"))
	class TSubclassOf<ACaptureTargetItem> CaptureTargetToSpawn;


public:
	AInterview_1GameMode();
	
	UFUNCTION(BlueprintCallable, Category = "CaptureTarget")
	void SpawnNewCaptureTargetItem();
	
	UFUNCTION(BlueprintCallable, Category = "CaptureTarget")
	void SpawnNewCaptureTargetsInBox(const int NumTargetsToSpawn, const int BoxExtent);
	
	UFUNCTION(BlueprintCallable, Category = "CaptureTarget")
	void SpawnNewCaptureTargetItemAtCursor();

	UFUNCTION(BlueprintCallable)
	void SetCaptureConfig(FCaptureConfig NewConfig);
	
	UFUNCTION(BlueprintCallable)
	FCaptureConfig  & GetCaptureConfig();

	UFUNCTION(BlueprintCallable)
	void StartCapture();
	
	UFUNCTION(BlueprintCallable)
	void StopCapture();
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsCapturing;
	
	UPROPERTY(BlueprintReadWrite)
	int FramesCaptured;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int RandomSamplesToCapture;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bRandomSample;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector RandomSampleStartLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RandomSampleRange;
	

	// Everything that extends the point of interest Interface
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "POI")
	TArray<AActor *> CapturePoints;


protected:

	virtual void BeginPlay() override;
	
	// configuration to use when capturing the data
	UPROPERTY()
	FCaptureConfig Config;

	UFUNCTION()
	void GetCapturePoints();

	virtual void Tick(float DeltaTime) override;

};



