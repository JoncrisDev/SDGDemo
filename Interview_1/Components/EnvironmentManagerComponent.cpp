#include "EnvironmentManagerComponent.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/LightComponent.h"
#include "Components/SkyLightComponent.h"
#include "ENgine/DirectionalLight.h"
#include "Engine/SkyLight.h"

#include "Kismet/GameplayStatics.h"

void UEnvironmentManagerComponent::SetDirectionalLightIntensity(float NewIntensity) const
{
	if (DirectionalLight)
	{
		DirectionalLight->SetBrightness(NewIntensity);
	}
}

float UEnvironmentManagerComponent::GetDirectionalLightIntensity() const
{
	if (DirectionalLight)
	{
		return DirectionalLight->GetBrightness();
	}
	return 0.0f;
}

void UEnvironmentManagerComponent::SetDirectionalLightTemperature(float NewTemperature) const
{
	if (DirectionalLight)
	{
		DirectionalLight->GetLightComponent()->SetTemperature(NewTemperature);
	}
}

float UEnvironmentManagerComponent::GetDirectionalLightTemperature() const
{
	if (DirectionalLight)
	{
		return DirectionalLight->GetLightComponent()->Temperature;
	}
	return 0.0f;
}

void UEnvironmentManagerComponent::SetDirectionalLightAngle(float NewAngle) const
{
	if (DirectionalLight)
	{
		UDirectionalLightComponent * LightComp = Cast<UDirectionalLightComponent>(DirectionalLight->GetLightComponent());
		LightComp->SetLightSourceAngle(NewAngle);
	}
}

float UEnvironmentManagerComponent::GetDirectionalLightAngle() const
{
	if (DirectionalLight)
	{
		UDirectionalLightComponent * LightComp = Cast<UDirectionalLightComponent>(DirectionalLight->GetLightComponent());
		return LightComp->LightSourceAngle;
	}
	return 0.0f;
}

void UEnvironmentManagerComponent::SetDirectionalLightEnabled(bool bEnabled) const
{
	DirectionalLight->SetEnabled(bEnabled);
}

bool UEnvironmentManagerComponent::GetDirectionalLightEnabled() const
{
	return DirectionalLight->IsEnabled();
}

float UEnvironmentManagerComponent::GetSkyLightIntensity() const
{
	if (SkyLight)
	{
		const USkyLightComponent * LightComponent = SkyLight->GetLightComponent();
		return LightComponent->Intensity;
	}
	return 0.0f;
}

void UEnvironmentManagerComponent::SetSkyLightIntensity(float NewIntensity) const
{
	if (SkyLight)
	{
		USkyLightComponent * LightComponent = SkyLight->GetLightComponent();
		LightComponent->SetIntensity(NewIntensity);
	}
}

float UEnvironmentManagerComponent::GetSkyLightGI() const
{
	if (SkyLight)
	{
		const USkyLightComponent * LightComponent = SkyLight->GetLightComponent();
		return LightComponent->IndirectLightingIntensity;
	}
	return 0.0f;
}

void UEnvironmentManagerComponent::SetSkyLightGI(float NewIntensity) const
{
	if (SkyLight)
	{
		USkyLightComponent * LightComponent = SkyLight->GetLightComponent();
		LightComponent->SetIndirectLightingIntensity(NewIntensity);
	}
}

void UEnvironmentManagerComponent::SetSkyLightEnabled(bool bEnabled) const
{
	if (SkyLight)
	{
		USkyLightComponent * LightComponent = SkyLight->GetLightComponent();
		LightComponent->bAffectsWorld = bEnabled;
	}
}

bool UEnvironmentManagerComponent::GetSkyLightEnabled() const
{
	if (SkyLight)
	{
		const USkyLightComponent * LightComponent = SkyLight->GetLightComponent();
		return LightComponent->bAffectsWorld; 
	}
	return false;
}


void UEnvironmentManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Acquire the levels directional light
	// NOTE: This acquires the first Directional light in the scene. Other lights will be ignored.
	TArray<AActor *> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), OutActors);
	if (ADirectionalLight* Light = Cast<ADirectionalLight>(OutActors.Top()))
	{
		DirectionalLight = Light;
	}

	// Acquire the first SkyLight
	OutActors.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASkyLight::StaticClass(), OutActors);
	if (ASkyLight* Light = Cast<ASkyLight>(OutActors.Top()))
	{
		SkyLight = Light;
	}
	
}

// Called every frame
void UEnvironmentManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
