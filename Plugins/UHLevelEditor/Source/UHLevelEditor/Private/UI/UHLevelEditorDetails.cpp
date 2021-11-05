// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#include "UI/UHLevelEditorDetails.h"
#include "UHLevelEditorEdMode.h"
#include "UI/UHLevelEditorEdModeToolkit.h"
#include "UI/UHLevelEditorDetailCustomization_NewLandscape.h"

#include "EditorModeManager.h"
#include "EditorModes.h"
#include "SlateOptMacros.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Framework/Commands/UICommandList.h"

#define LOCTEXT_NAMESPACE "UHLevelEditor"

FUHLevelEditorDetails::FUHLevelEditorDetails()
{

}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void FUHLevelEditorDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	FUHLevelEditorEdMode* EdMode = GetEditorMode();

	IDetailCategoryBuilder& LandscapeEditorCategory = DetailBuilder.EditCategory("LandscapeEditor", FText::GetEmpty(), ECategoryPriority::TypeSpecific);

	Customization_NewLandscape = MakeShareable(new FUHLevelEditorDetailCustomization_NewLandscape);
	Customization_NewLandscape->CustomizeDetails(DetailBuilder);
}

void FUHLevelEditorDetails::CustomizeToolPalette(class FToolBarBuilder& ToolbarBuilder, const TSharedRef<class FUHLevelEditorEdModeToolkit> Toolkit)
{
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<IDetailCustomization> FUHLevelEditorDetails::MakeInstance()
{
	return MakeShareable(new FUHLevelEditorDetails);
}

#undef LOCTEXT_NAMESPACE