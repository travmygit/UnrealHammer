// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#include "UI/UHLevelEditorDetails.h"
#include "UHLevelEditorEdMode.h"
#include "UI/UHLevelEditorUISettings.h"
#include "UI/UHLevelEditorEdModeToolkit.h"
#include "UI/UHLevelEditorDetailCustomization_NewLandscape.h"

#include "EditorModeManager.h"
#include "EditorModes.h"
#include "SlateOptMacros.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/Input/NumericTypeInterface.h"
#include "VariablePrecisionNumericInterface.h"
#include "Framework/Commands/UICommandList.h"

#define LOCTEXT_NAMESPACE "UHLevelEditor"

FUHLevelEditorDetails::FUHLevelEditorDetails()
{

}

void FUHLevelEditorDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	CommandList = EdMode->GetToolkitCommands();

	IDetailCategoryBuilder& LandscapeEditorCategory = DetailBuilder.EditCategory("LandscapeEditor", FText::GetEmpty(), ECategoryPriority::TypeSpecific);

	Customization_NewLandscape = MakeShareable(new FUHLevelEditorDetailCustomization_NewLandscape);
	Customization_NewLandscape->CustomizeDetails(DetailBuilder);
}

void FUHLevelEditorDetails::CustomizeToolPalette(class FToolBarBuilder& ToolbarBuilder, const TSharedRef<class FUHLevelEditorEdModeToolkit> Toolkit)
{
	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	CommandList = EdMode->GetToolkitCommands();

	TSharedPtr<INumericTypeInterface<float> > NumericTypeInterface = MakeShareable(new FVariablePrecisionNumericInterface());

	// Tool Strength
	FProperty* ToolStrengthProperty = EdMode->UISettings->GetClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UUHLevelEditorUISettings, ToolStrength));
	const FString& UIMinString = ToolStrengthProperty->GetMetaData("UIMin");
	const FString& UIMaxString = ToolStrengthProperty->GetMetaData("UIMax");
	const FString& SliderExponentString = ToolStrengthProperty->GetMetaData("SliderExponent");
	float UIMin = TNumericLimits<float>::Lowest();
	float UIMax = TNumericLimits<float>::Max();
	TTypeFromString<float>::FromString(UIMin, *UIMinString);
	TTypeFromString<float>::FromString(UIMax, *UIMaxString);
	float SliderExponent = 1.f;
	if (SliderExponentString.Len())
	{
		TTypeFromString<float>::FromString(SliderExponent, *SliderExponentString);
	}

	TSharedRef<SWidget> ToolStrengthWidget = SNew(SSpinBox<float>);

	ToolbarBuilder.AddToolBarWidget(ToolStrengthWidget, LOCTEXT("ToolStrength", "Strength"));


}

TSharedRef<IDetailCustomization> FUHLevelEditorDetails::MakeInstance()
{
	return MakeShareable(new FUHLevelEditorDetails);
}

#undef LOCTEXT_NAMESPACE