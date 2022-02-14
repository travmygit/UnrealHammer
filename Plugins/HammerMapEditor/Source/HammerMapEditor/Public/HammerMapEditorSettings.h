#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "HammerMapEditorSettings.generated.h"

UCLASS(MinimalAPI, config = HammerMapEditor, defaultconfig)
class UHammerMapEditorSettings : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(config, EditAnywhere, Category = Panel, AdvancedDisplay)
	FSoftObjectPath MainPanel;

};