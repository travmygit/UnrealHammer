#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UHLevelEditorUISettings.generated.h"

UCLASS(MinimalAPI)
class UUHLevelEditorUISettings : public UObject
{
	GENERATED_BODY()

public:

	UUHLevelEditorUISettings();

	// EdMode that owns this.
	class FUHLevelEditorEdMode* EdMode;

	// The location of the new landscape.
	UPROPERTY(Category = "New Landscape", EditAnywhere, meta = (ShowForTools = "NewLandscape", DisplayName = "Location"))
	FVector NewLandscape_Location;

	// The rotation of the new landscape.
	UPROPERTY(Category = "New Landscape", EditAnywhere, meta = (ShowForTools = "NewLandscape", DisplayName = "Rotation"))
	FRotator NewLandscape_Rotation;

	// The scale of the new landscape. This is the distance between each vertex on the landscape, defaulting to 100 units.
	UPROPERTY(Category = "New Landscape", EditAnywhere, meta = (ShowForTools = "NewLandscape", DisplayName = "Scale"))
	FVector NewLandscape_Scale;

	// The number of quads in a single landscape component.
	UPROPERTY(Category = "New Landscape", EditAnywhere, meta = (ShowForTools = "NewLandscape", DisplayName = "Size Per Component"))
	int32 NewLandscape_ComponentSize;
	
	// The number of components in the X and Y direction, determining the overall size of the landscape.
	UPROPERTY(Category = "New Landscape", EditAnywhere, meta = (ShowForTools = "NewLandscape", DisplayName = "Number of Components"))
	FIntPoint NewLandscape_ComponentCount;

public:

	// Called to initialize newly created UI settings.
	void Init(class FUHLevelEditorEdMode* InEdMode);

};