// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonRoomManager.generated.h"

UCLASS()
class PROMETHEUS_API ADungeonRoomManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonRoomManager();

	// in editor Button to collect all the SnapMarkers
	UFUNCTION(CallInEditor, Category = "Dungeon")
	void CollectSnapMarkers();

	UFUNCTION(CallInEditor, Category = "Dungeon")
	void UpdateLevelBounds();

	UPROPERTY(VisibleAnywhere, Category = "Dungeon")
	FBox LevelBounds;

private:
	UPROPERTY(VisibleAnywhere, Category = "Dungeon")
	TArray<class ASnapDungeonMarkerActor*> SnapMarkerActors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dungeon")
	TArray<class ASnapDungeonMarkerActor*> GetSnapMarkers() const { return SnapMarkerActors; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dungeon")
	TArray<class ASnapDungeonMarkerActor*> GetSnapMarkersWithTag(FString markerName) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dungeon")
	bool IsActorInRoomBounds(AActor* Actor) const;

private:
	void ShiftLevelBounds();
};
