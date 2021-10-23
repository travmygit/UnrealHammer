#include "UHLevelEditorDetails.h"
#include "EditorModeManager.h"
#include "EditorModes.h"
#include "SlateOptMacros.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Framework/Commands/UICommandList.h"
#include "UHLevelEditorEdMode.h"
#include "UHLevelEditorDetailCustomization_NewLandscape.h"

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
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<IDetailCustomization> FUHLevelEditorDetails::MakeInstance()
{
	return MakeShareable(new FUHLevelEditorDetails);
}

#undef LOCTEXT_NAMESPACE