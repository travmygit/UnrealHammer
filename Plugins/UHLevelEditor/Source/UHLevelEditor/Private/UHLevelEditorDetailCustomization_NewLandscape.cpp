#include "UHLevelEditorDetailCustomization_NewLandscape.h"
#include "EditorModeManager.h"
#include "EditorModes.h"
#include "SlateOptMacros.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "UHLevelEditorEdMode.h"

#define LOCTEXT_NAMESPACE "UHLevelEditor.NewLandscape"

FUHLevelEditorDetailCustomization_NewLandscape::FUHLevelEditorDetailCustomization_NewLandscape()
{

}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void FUHLevelEditorDetailCustomization_NewLandscape::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	static const FName NAME_NewLandscape = TEXT("NewLandscape");

	if (!IsToolActive(NAME_NewLandscape))
	{
		return;
	}

	IDetailCategoryBuilder& NewLandscapeCategory = DetailBuilder.EditCategory("New Landscape");

	NewLandscapeCategory.AddCustomRow(FText::GetEmpty())
	[
		SNew(SUniformGridPanel)
		.SlotPadding(FMargin(10, 2))
		+ SUniformGridPanel::Slot(0, 0)
		[
			SNew(SCheckBox)
			.Style(FEditorStyle::Get(), "RadioButton")
			.IsChecked(this, &FUHLevelEditorDetailCustomization_NewLandscape::NewLandscapeModeIsChecked, EUHNewLandscapePreviewMode::NewLandscape)
			.OnCheckStateChanged(this, &FUHLevelEditorDetailCustomization_NewLandscape::OnNewLandscapeModeChanged, EUHNewLandscapePreviewMode::NewLandscape)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("NewLandscape", "Create New"))
			]
		]
		+ SUniformGridPanel::Slot(1, 0)
		[
			SNew(SCheckBox)
			.Style(FEditorStyle::Get(), "RadioButton")
			.IsChecked(this, &FUHLevelEditorDetailCustomization_NewLandscape::NewLandscapeModeIsChecked, EUHNewLandscapePreviewMode::ImportLandscape)
			.OnCheckStateChanged(this, &FUHLevelEditorDetailCustomization_NewLandscape::OnNewLandscapeModeChanged, EUHNewLandscapePreviewMode::ImportLandscape)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ImportLandscape", "Import from File"))
			]
		]
	];


}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<IDetailCustomization> FUHLevelEditorDetailCustomization_NewLandscape::MakeInstance()
{
	return MakeShareable(new FUHLevelEditorDetailCustomization_NewLandscape);
}

ECheckBoxState FUHLevelEditorDetailCustomization_NewLandscape::NewLandscapeModeIsChecked(EUHNewLandscapePreviewMode Mode) const
{
	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		return (EdMode->NewLandscapePreviewMode == Mode) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
	}
	return ECheckBoxState::Unchecked;
}

void FUHLevelEditorDetailCustomization_NewLandscape::OnNewLandscapeModeChanged(ECheckBoxState NewCheckedState, EUHNewLandscapePreviewMode Mode)
{
	if (NewCheckedState == ECheckBoxState::Checked)
	{
		FUHLevelEditorEdMode* EdMode = GetEditorMode();
		if (EdMode)
		{
			EdMode->NewLandscapePreviewMode = Mode;
		}
	}
}

#undef LOCTEXT_NAMESPACE