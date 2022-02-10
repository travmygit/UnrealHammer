#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "HammerMapEditorPanelBase.generated.h"

UCLASS(MinimalAPI)
class UHammerMapEditorPanelBase : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	
	UHammerMapEditorPanelBase(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;
	virtual void BeginDestroy() override;

protected:
	

};