
#include "Widget_PointOfInterestItem.h"
#include "Interview_1/Actors/CaptureTargetItem.h"

// @todo: These UMG bindings are pretty poor for performance, they should be moved to transaction get/set when refactoring.

void UWidget_PointOfInterestItem::TargetMove_X(float NewXLocation) const
{
	if (CaptureTarget)
	{
		const FVector CurrentLocation = CaptureTarget->GetActorLocation();
		CaptureTarget->SetActorLocation(FVector(NewXLocation, CurrentLocation.Y, CurrentLocation.Z));
	}
}

void UWidget_PointOfInterestItem::TargetMove_Y(float NewYLocation) const
{
	if (CaptureTarget)
	{
		const FVector CurrentLocation = CaptureTarget->GetActorLocation();
		CaptureTarget->SetActorLocation(FVector(CurrentLocation.X, NewYLocation, CurrentLocation.Z));
	}
}

void UWidget_PointOfInterestItem::TargetMove_Z(float NewZLocation) const
{
	if (CaptureTarget)
	{
		const FVector CurrentLocation = CaptureTarget->GetActorLocation();
		CaptureTarget->SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, NewZLocation));
	}
}

void UWidget_PointOfInterestItem::TargetRotate_Pitch(float Pitch) const
{
	if (CaptureTarget)
	{
		const FRotator CurrentRotation = CaptureTarget->GetActorRotation();
		CaptureTarget->SetActorRotation(FRotator(Pitch, CurrentRotation.Roll, CurrentRotation.Yaw));
	}
}

void UWidget_PointOfInterestItem::TargetRotate_Yaw(float Roll) const
{
	if (CaptureTarget)
	{
		const FRotator CurrentRotation = CaptureTarget->GetActorRotation();
		CaptureTarget->SetActorRotation(FRotator(CurrentRotation.Pitch, Roll, CurrentRotation.Yaw));
	}
}

void UWidget_PointOfInterestItem::TargetRotate_Roll(float Yaw) const
{
	if (CaptureTarget)
	{
		const FRotator CurrentRotation = CaptureTarget->GetActorRotation();
		CaptureTarget->SetActorRotation(FRotator(CurrentRotation.Pitch, CurrentRotation.Roll, Yaw));
	}
}

void UWidget_PointOfInterestItem::TargetUpdateMaterial(int NewMaterialIdx) const
{
	if (CaptureTarget)
	{
		CaptureTarget->ChangeMaterial(NewMaterialIdx);
	}
}

void UWidget_PointOfInterestItem::TargetChangeMesh(int NewMeshID) const
{
	if (CaptureTarget)
	{
		// CaptureTarget->ChangeMaterial(NewMaterialIdx);
		// Just do a set mesh call here to save time.
	}
}
