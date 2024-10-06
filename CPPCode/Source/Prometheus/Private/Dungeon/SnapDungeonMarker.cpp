// Fill out your copyright notice in the Description page of Project Settings.


#include "Dungeon/SnapDungeonMarker.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"

ASnapDungeonMarkerActor::ASnapDungeonMarkerActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SnapDungeonMarkerComponent = ObjectInitializer.CreateDefaultSubobject<USnapDungeonMarkerComponent>(this, "MarkerComponent");
	SnapDungeonMarkerComponent->SetMobility(EComponentMobility::Static);
	RootComponent = SnapDungeonMarkerComponent;

#if WITH_EDITORONLY_DATA
	ArrowComponent = ObjectInitializer.CreateEditorOnlyDefaultSubobject<UArrowComponent>(this, TEXT("Arrow"));
	SpriteComponent = ObjectInitializer.CreateEditorOnlyDefaultSubobject<UBillboardComponent>(this, TEXT("Sprite"));

	if (!IsRunningCommandlet()) {
		if (ArrowComponent) {
			ArrowComponent->SetMobility(EComponentMobility::Static);
			ArrowComponent->SetupAttachment(RootComponent);
			ArrowComponent->SetHiddenInGame(true);
		}

		if (SpriteComponent) {
			SpriteComponent->SetMobility(EComponentMobility::Static);
			SpriteComponent->SetupAttachment(RootComponent);
			SpriteComponent->SetHiddenInGame(true);
		}
	};
#endif // WITH_EDITORONLY_DATA
}

void ASnapDungeonMarkerActor::PostLoad() {
	Super::PostLoad();

	Initialize();
}

void ASnapDungeonMarkerActor::PostActorCreated() {
	Super::PostActorCreated();

	Initialize();
}

void ASnapDungeonMarkerActor::PostDuplicate(EDuplicateMode::Type DuplicateMode) {
	Super::PostDuplicate(DuplicateMode);

}

void ASnapDungeonMarkerActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// instantiate new marker asset from marker asset subclass
	if (MarkerAssetClass) {
		SnapDungeonMarkerComponent->MarkerAsset = NewObject<USnapDungeonMarkerAsset>(this, MarkerAssetClass);
	}
}

TArray<FString> ASnapDungeonMarkerActor::GetAllowedMarkerNames() const {
	TArray<FString> Result;
	if (SnapDungeonMarkerComponent && SnapDungeonMarkerComponent->MarkerAsset) {
		Result = SnapDungeonMarkerComponent->MarkerAsset->MarkerNames;
	}
	return Result;
}

#if WITH_EDITOR
void ASnapDungeonMarkerActor::PostEditChangeProperty(FPropertyChangedEvent& e) {
	Super::PostEditChangeProperty(e);

	Initialize();
}
#endif

void ASnapDungeonMarkerActor::Initialize() {
#if WITH_EDITORONLY_DATA
	USnapDungeonMarkerAsset* markerAss = SnapDungeonMarkerComponent ? SnapDungeonMarkerComponent->MarkerAsset : nullptr;
	if(markerAss && markerAss->PreviewSprite && SpriteComponent) {
		SpriteComponent->SetSprite(markerAss->PreviewSprite);
		SpriteComponent->SetRelativeScale3D(FVector(markerAss->PreviewSpriteSettings.Scale));
		SpriteComponent->SetRelativeLocation(FVector(0, 0, markerAss->PreviewSpriteSettings.OffsetZ));
	}
#endif // WITH_EDITOR_ONLY_DATA

}