#pragma once

#include "CoreMinimal.h"
#include "Templates/Casts.h"
#include "IDetailCustomization.h"
#include "PropertyHandle.h"
#include "UHLevelEditorDetailCustomization_Base.h"

class FUHLevelEditorEdMode;
class IDetailLayoutBuilder;
class FUICommandList;
class FUHLevelEditorDetailCustomization_NewLandscape;

/**
 * Slate widgets customizer for the "New Landscape" tool
 */
class FUHLevelEditorDetails : public FUHLevelEditorDetailCustomization_Base
{
public:

	FUHLevelEditorDetails();

	//////////////////////////////////////////////////////////////////////////
	//~ Begin IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	//~ End IDetailCustomization interface
	//////////////////////////////////////////////////////////////////////////

public:
	static TSharedRef<IDetailCustomization> MakeInstance();

protected:
	TSharedPtr<FUICommandList> CommandList;
	TSharedPtr<FUHLevelEditorDetailCustomization_NewLandscape> Customization_NewLandscape;
};