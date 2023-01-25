// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SDGStaticsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class INTERVIEW_1_API USDGStaticsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	static TMap<FString, FString> GetAllActorNamesAndIDs();
	
};
