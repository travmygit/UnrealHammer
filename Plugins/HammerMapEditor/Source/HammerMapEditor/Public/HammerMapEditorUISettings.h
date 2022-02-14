#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "HammerMapEditorUISettings.generated.h"

UCLASS(MinimalAPI, config = HammerMapEditor, defaultconfig)
class UHammerMapEditorUISettings : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = NewLandscape)
	FTransform NewLandscapeTransfrom;
};