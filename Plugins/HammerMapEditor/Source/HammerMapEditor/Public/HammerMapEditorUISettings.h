#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "HammerMapEditorUISettings.generated.h"

UCLASS(MinimalAPI, config = HammerMapEditor, defaultconfig)
class UHammerMapEditorUISettings : public UObject
{
	GENERATED_BODY()

public:

	UHammerMapEditorUISettings()
	: MapSize(64)
	, BrushType()
	, BrushSize()
	{
	}
	
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = ManageTool)
	FIntPoint MapSize;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = TileEditor)
	int32 BrushType;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = TileEditor)
	int32 BrushSize;
};