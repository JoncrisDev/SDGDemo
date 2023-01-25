#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnvironmentManagerComponent.generated.h"

class ADirectionalLight;
class ASkyLight;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERVIEW_1_API UEnvironmentManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Lighting controls

	// Directional Lighting
	UFUNCTION(BlueprintCallable, Category = "Lighting")
	void SetDirectionalLightIntensity(float NewIntensity) const;

	UFUNCTION(BlueprintCallable, Category = "Lighting")
	float GetDirectionalLightIntensity() const;
	
	UFUNCTION(BlueprintCallable, Category = "Lighting")
	void SetDirectionalLightTemperature(float NewTemperature) const;

	UFUNCTION(BlueprintCallable, Category = "Lighting")
	float GetDirectionalLightTemperature() const;
	
	UFUNCTION(BlueprintCallable, Category = "Lighting")
	void SetDirectionalLightAngle(float NewAngle) const;

	UFUNCTION(BlueprintCallable, Category = "Lighting")
	float GetDirectionalLightAngle() const;
	
	UFUNCTION(BlueprintCallable, Category = "Lighting")
	void SetDirectionalLightEnabled(bool bEnabled) const;
	
	UFUNCTION(BlueprintCallable, Category = "Lighting")
	bool GetDirectionalLightEnabled() const;

	// Sky Light
	UFUNCTION(BlueprintCallable, Category = "Lighting")
	float GetSkyLightIntensity() const;
	
	UFUNCTION(BlueprintCallable, Category = "Lighting")
	void SetSkyLightIntensity(float NewIntensity) const;
	
	UFUNCTION(BlueprintCallable, Category = "Lighting")
	float GetSkyLightGI() const;
	
	UFUNCTION(BlueprintCallable, Category = "Lighting")
	void SetSkyLightGI(float NewIntensity) const;
	
	UFUNCTION(BlueprintCallable, Category = "Lighting")
	void SetSkyLightEnabled(bool bEnabled) const;
	
	UFUNCTION(BlueprintCallable, Category = "Lighting")
	bool GetSkyLightEnabled() const;

protected:
	
	virtual void BeginPlay() override;

	// World Lighting
	TObjectPtr<ADirectionalLight> DirectionalLight;
	TObjectPtr<ASkyLight> SkyLight;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
