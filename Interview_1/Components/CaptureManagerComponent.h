// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CaptureManagerComponent.generated.h"

class ACaptureCamera;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERVIEW_1_API UCaptureManagerComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACaptureCamera>  CaptureCamera;

public:	
	// Sets default values for this component's properties
	UCaptureManagerComponent();

	UFUNCTION()
	virtual void StartCapture();

	UFUNCTION()
	virtual void StopCapture();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int FramesToCapture;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
