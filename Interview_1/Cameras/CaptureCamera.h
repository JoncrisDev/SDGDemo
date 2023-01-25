// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interview_1/Actors/CaptureTargetItem.h"
#include "CaptureCamera.generated.h"

UCLASS()
class INTERVIEW_1_API ACaptureCamera : public AActor
{
	GENERATED_BODY()
	
	// Responsible for capturing the scene
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* Camera;
	
public:	
	// Sets default values for this actor's properties
	ACaptureCamera();

	UFUNCTION()
	void StartCapture();
	
	UFUNCTION()
	void StopCapture();

	bool bIsCapturing;
	
	UPROPERTY()
	TArray<ACaptureTargetItem *> ItemsToPanorama;

	int PanoramaFrames;

	int PanoramaFramesDone;
	
	// @todo: (move to protected native only) Making public for debug
	UFUNCTION(BlueprintCallable)
	virtual void Capture(FString FileLabel) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void CapturePanoramaItem(ACaptureTargetItem* Target);

	UFUNCTION()
	virtual void CaptureRandomSample();

	// used for computing a random capture sample in a bounds volume
	UPROPERTY()
	FVector CameraStartPosition;

	int RandomSamples;

	float BoxExtent;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
