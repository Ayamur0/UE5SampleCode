// Fill out your copyright notice in the Description page of Project Settings.


#include "Dungeon/DungeonRoomManager.h"

#include "EngineUtils.h"
#include "Engine/LevelBounds.h"
#include "Components/BoxComponent.h"
#include "Dungeon/SnapDungeonMarker.h"

// Sets default values
ADungeonRoomManager::ADungeonRoomManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bRelevantForLevelBounds = false;

}

void ADungeonRoomManager::CollectSnapMarkers()
{
	SnapMarkerActors.Empty();

	// Find all SnapDungeonMarkerActors in the level
	for (TActorIterator<ASnapDungeonMarkerActor> It(GetWorld()); It; ++It)
	{
		ASnapDungeonMarkerActor* SnapMarker = *It;
		if (SnapMarker)
		{
			SnapMarkerActors.Add(SnapMarker);
		}
	}
}

void ADungeonRoomManager::UpdateLevelBounds()
{
	ALevelBounds* LevelBoundsActor = nullptr;
	for (TActorIterator<ALevelBounds> It(GetWorld()); It; ++It)
	{
		LevelBoundsActor = *It;
		break;
	}
	
	if (LevelBoundsActor)
	{
		UBoxComponent* comp = LevelBoundsActor->BoxComponent;
		LevelBounds = comp->Bounds.GetBox();
	}
}

// Called when the game starts or when spawned
void ADungeonRoomManager::BeginPlay()
{
	ShiftLevelBounds();
	Super::BeginPlay();
}

// Called every frame
void ADungeonRoomManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<class ASnapDungeonMarkerActor*> ADungeonRoomManager::GetSnapMarkersWithTag(FString markerName) const
{
	TArray<ASnapDungeonMarkerActor*> Result;
	for (ASnapDungeonMarkerActor* SnapMarker : SnapMarkerActors)
	{
		if (SnapMarker->GetAllowedMarkerNames().Contains(markerName))
		{
			Result.Add(SnapMarker);
		}
	}
	return Result;
}

bool ADungeonRoomManager::IsActorInRoomBounds(AActor* Actor) const
{
	if (Actor)
	{
		FVector ActorLocation = Actor->GetActorLocation();
		return LevelBounds.IsInside(ActorLocation);
	}
	return false;
}

void ADungeonRoomManager::ShiftLevelBounds()
{
	FVector Center = LevelBounds.GetCenter();
	FVector NewCenter = GetActorLocation();
	FVector Offset = NewCenter - Center;

	LevelBounds = LevelBounds.ShiftBy(Offset);
}


