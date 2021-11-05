// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/Casts.h"
#include "IDetailCustomization.h"
#include "PropertyHandle.h"
#include "UI/UHLevelEditorDetailCustomization_Base.h"

class FUHLevelEditorEdMode;
class IDetailLayoutBuilder;
class FUICommandList;
class FUHLevelEditorDetailCustomization_NewLandscape;

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorDetails

class FUHLevelEditorDetails : public FUHLevelEditorDetailCustomization_Base
{
public:

	FUHLevelEditorDetails();

	//////////////////////////////////////////////////////////////////////////
	//~ Begin IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	//~ End IDetailCustomization interface
	//////////////////////////////////////////////////////////////////////////

	void CustomizeToolPalette(class FToolBarBuilder& ToolbarBuilder, const TSharedRef<class FUHLevelEditorEdModeToolkit> Toolkit);

public:
	static TSharedRef<IDetailCustomization> MakeInstance();

protected:
	TSharedPtr<FUICommandList> CommandList;
	TSharedPtr<FUHLevelEditorDetailCustomization_NewLandscape> Customization_NewLandscape;
};