#include "SDGStaticsLibrary.h"

#include "Kismet/GameplayStatics.h"

TMap<FString, FString> USDGStaticsLibrary::GetAllActorNamesAndIDs()
{
	TArray<AActor *> OutActors;
	TMap<FString, FString> OutNamesAndIDs;
	UGameplayStatics::GetAllActorsOfClass(GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World(), AActor::StaticClass(), OutActors);
	for (auto const Actor : OutActors)
	{
		OutNamesAndIDs.Add(Actor->GetName(), Actor->GetPathName());
	}
	return OutNamesAndIDs;
}
