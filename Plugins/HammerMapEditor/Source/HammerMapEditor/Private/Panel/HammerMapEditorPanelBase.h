#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "HammerMapEditorPanelBase.generated.h"

class UHammerMapEditorUISettings;

UCLASS(MinimalAPI)
class UHammerMapEditorPanelBase : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	
	UHammerMapEditorPanelBase(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;
	virtual void BeginDestroy() override;

protected:

	/// Returns the UI profile object.
	UFUNCTION(BlueprintPure)
	UHammerMapEditorUISettings* GetUISettings() const;
};