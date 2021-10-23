#pragma once

#include "CoreMinimal.h"
#include "Templates/Casts.h"
#include "IDetailCustomization.h"
#include "PropertyHandle.h"
#include "UHLevelEditorEdMode.h"
#include "UHLevelEditorDetailCustomization_Base.h"

class FUHLevelEditorEdMode;
class IDetailLayoutBuilder;

/**
 * Slate widgets customizer for the "New Landscape" tool
 */
class FUHLevelEditorDetailCustomization_NewLandscape : public FUHLevelEditorDetailCustomization_Base
{
public:
	
	FUHLevelEditorDetailCustomization_NewLandscape();

	//////////////////////////////////////////////////////////////////////////
	//~ Begin IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	//~ End IDetailCustomization interface
	//////////////////////////////////////////////////////////////////////////

public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	ECheckBoxState NewLandscapeModeIsChecked(EUHNewLandscapePreviewMode Mode) const;
	void OnNewLandscapeModeChanged(ECheckBoxState NewCheckedState, EUHNewLandscapePreviewMode Mode);
};