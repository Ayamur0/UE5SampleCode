// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "SnapDungeonMarker.generated.h"

class UArrowComponent;

USTRUCT()
struct PROMETHEUS_API FSnapDungeonMarkerAssetSpriteSettings {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Dungeon)
    float Scale = 1.0f;

    UPROPERTY(EditAnywhere, Category = Dungeon)
    float OffsetZ = 0.0f;
};

UCLASS(Blueprintable)
class PROMETHEUS_API USnapDungeonMarkerAsset : public UObject {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Dungeon")
    TArray<FString> MarkerNames;

#if WITH_EDITORONLY_DATA
    /** An editor-only sprite to attach to the placed actor. This is purely for visual purpose while designing your levels */
    UPROPERTY(EditAnywhere, Category = "Dungeon")
    UTexture2D* PreviewSprite = nullptr;

    UPROPERTY(EditAnywhere, Category = "Dungeon")
    FSnapDungeonMarkerAssetSpriteSettings PreviewSpriteSettings;
#endif // WITH_EDITORONLY_DATA
};

/**
 * Place a marker on to the world.   If the theme engine picks this component up (which depends on the builder),
 * then it will spawn the objects defined in the theme file under the specified marker name
 */
UCLASS(Blueprintable, HideCategories = (Rendering, Input, Actor, Misc, Replication, Collision, LOD, Cooking))
class PROMETHEUS_API USnapDungeonMarkerComponent : public USceneComponent {
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, Category = "Dungeon")
    USnapDungeonMarkerAsset* MarkerAsset = nullptr;

};

UCLASS(Blueprintable, ConversionRoot, ComponentWrapperClass, HideCategories = (Rendering, Input, Actor, Misc, Replication, Collision, LOD, Cooking))
class PROMETHEUS_API ASnapDungeonMarkerActor : public AActor {
    GENERATED_UCLASS_BODY()
public:
    UPROPERTY(Category = "Dungeon", BlueprintReadOnly, meta = (ExposeFunctionCategories = "Dungeon", AllowPrivateAccess = "true"))
    USnapDungeonMarkerComponent* SnapDungeonMarkerComponent;

    UPROPERTY(EditAnywhere, Category = "Dungeon")
    TSubclassOf<USnapDungeonMarkerAsset> MarkerAssetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
    bool bIsOccupied = false;

#if WITH_EDITORONLY_DATA
    UPROPERTY()
    UBillboardComponent* SpriteComponent;

    UPROPERTY(Transient)
    UArrowComponent* ArrowComponent;
#endif // WITH_EDITORONLY_DATA

public:
    virtual void PostLoad() override;
    virtual void PostActorCreated() override;
    virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
    virtual void OnConstruction(const FTransform& Transform) override;
    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    virtual TArray<FString> GetAllowedMarkerNames() const;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
#endif

protected:
    virtual void Initialize();
};
