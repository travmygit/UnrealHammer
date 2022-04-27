#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Panel/HammerMapEditorPanelBase.h"
#include "HammerMapEditorMainPanel.generated.h"

UCLASS(MinimalAPI)
class UHammerMapEditorMainPanel : public UHammerMapEditorPanelBase
{
	GENERATED_BODY()

public:

	UHammerMapEditorMainPanel(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;
	virtual void BeginDestroy() override;

protected:

};