#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PointOfInterest.generated.h"

UINTERFACE(MinimalAPI)
class UPointOfInterest : public UInterface
{
	GENERATED_BODY()
};

class INTERVIEW_1_API IPointOfInterest
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	virtual void CapturePanorama() const;


};
