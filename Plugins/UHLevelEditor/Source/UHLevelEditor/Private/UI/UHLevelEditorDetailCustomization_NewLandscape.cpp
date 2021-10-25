// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#include "UI/UHLevelEditorDetailCustomization_NewLandscape.h"
#include "UHLevelEditorEdMode.h"

#include "EditorModeManager.h"
#include "EditorModes.h"
#include "SlateOptMacros.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/Input/SNumericEntryBox.h"

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
			.IsChecked(this, &FUHLevelEditorDetailCustomization_NewLandscape::NewLandscapeModeIsChecked, EUHLevelEditorNewLandscapeMethod::NewLandscape)
			.OnCheckStateChanged(this, &FUHLevelEditorDetailCustomization_NewLandscape::OnNewLandscapeModeChanged, EUHLevelEditorNewLandscapeMethod::NewLandscape)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("NewLandscape", "Create New"))
			]
		]
		+ SUniformGridPanel::Slot(1, 0)
		[
			SNew(SCheckBox)
			.Style(FEditorStyle::Get(), "RadioButton")
			.IsChecked(this, &FUHLevelEditorDetailCustomization_NewLandscape::NewLandscapeModeIsChecked, EUHLevelEditorNewLandscapeMethod::ImportLandscape)
			.OnCheckStateChanged(this, &FUHLevelEditorDetailCustomization_NewLandscape::OnNewLandscapeModeChanged, EUHLevelEditorNewLandscapeMethod::ImportLandscape)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ImportLandscape", "Import from File"))
			]
		]
	];

	TSharedRef<IPropertyHandle> PropertyHandle_ComponentCount = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UUHLevelEditorUISettings, NewLandscape_ComponentCount));
	TSharedRef<IPropertyHandle> PropertyHandle_ComponentCount_X = PropertyHandle_ComponentCount->GetChildHandle("X").ToSharedRef();
	TSharedRef<IPropertyHandle> PropertyHandle_ComponentCount_Y = PropertyHandle_ComponentCount->GetChildHandle("Y").ToSharedRef();
	NewLandscapeCategory.AddProperty(PropertyHandle_ComponentCount)
	.CustomWidget()
	.NameContent()
	[
		PropertyHandle_ComponentCount->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.FillWidth(1)
		[
			SNew(SNumericEntryBox<int32>)
			.LabelVAlign(VAlign_Center)
			.Font(DetailBuilder.GetDetailFont())
			.MinValue(1)
			.MaxValue(32)
			.MinSliderValue(1)
			.MaxSliderValue(32)
			.AllowSpin(true)
			.UndeterminedString(NSLOCTEXT("PropertyEditor", "MultipleValues", "Multiple Values"))
			.Value_Static(&FUHLevelEditorDetailCustomization_Base::OnGetValue<int32>, PropertyHandle_ComponentCount_X)
			.OnValueChanged_Static(&FUHLevelEditorDetailCustomization_Base::OnValueChanged<int32>, PropertyHandle_ComponentCount_X)
			.OnValueCommitted_Static(&FUHLevelEditorDetailCustomization_Base::OnValueCommitted<int32>, PropertyHandle_ComponentCount_X)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2, 0)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Font(DetailBuilder.GetDetailFont())
			.Text(FText::FromString(FString().AppendChar(0xD7))) // Multiply sign
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1)
		[
			SNew(SNumericEntryBox<int32>)
			.LabelVAlign(VAlign_Center)
			.Font(DetailBuilder.GetDetailFont())
			.MinValue(1)
			.MaxValue(32)
			.MinSliderValue(1)
			.MaxSliderValue(32)
			.AllowSpin(true)
			.UndeterminedString(NSLOCTEXT("PropertyEditor", "MultipleValues", "Multiple Values"))
			.Value_Static(&FUHLevelEditorDetailCustomization_Base::OnGetValue<int32>, PropertyHandle_ComponentCount_Y)
			.OnValueChanged_Static(&FUHLevelEditorDetailCustomization_Base::OnValueChanged<int32>, PropertyHandle_ComponentCount_Y)
			.OnValueCommitted_Static(&FUHLevelEditorDetailCustomization_Base::OnValueCommitted<int32>, PropertyHandle_ComponentCount_Y)
		]
	];

	NewLandscapeCategory.AddCustomRow(FText::GetEmpty())
	.NameContent()
	[
		SNew(SBox)
		.VAlign(VAlign_Center)
		.Padding(FMargin(2))
		[
			SNew(STextBlock)
			.Font(DetailBuilder.GetDetailFont())
			.Text(LOCTEXT("Resolution", "Resolution"))
		]
	]
	.ValueContent()
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.FillWidth(1)
		[
			SNew(SEditableTextBox)
			.IsReadOnly(true)
			.Font(DetailBuilder.GetDetailFont())
			.Text(this, &FUHLevelEditorDetailCustomization_NewLandscape::GetResolutionX)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2, 0)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Font(DetailBuilder.GetDetailFont())
			.Text(FText::FromString(FString().AppendChar(0xD7))) // Multiply sign
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1)
		[
			SNew(SEditableTextBox)
			.IsReadOnly(true)
			.Font(DetailBuilder.GetDetailFont())
			.Text(this, &FUHLevelEditorDetailCustomization_NewLandscape::GetResolutionY)
		]
	];

	NewLandscapeCategory.AddCustomRow(FText::GetEmpty())
	.NameContent()
	[
		SNew(SBox)
		.VAlign(VAlign_Center)
		.Padding(FMargin(2))
		[
			SNew(STextBlock)
			.Font(DetailBuilder.GetDetailFont())
			.Text(LOCTEXT("TotalComponents", "Total Components"))
		]
	]
	.ValueContent()
	[
		SNew(SBox)
		.Padding(FMargin(0, 0, 12, 0)) // Line up with the other properties due to having no reset to default button
		[
			SNew(SEditableTextBox)
			.IsReadOnly(true)
			.Font(DetailBuilder.GetDetailFont())
			.Text(this, &FUHLevelEditorDetailCustomization_NewLandscape::GetTotalComponentCount)
		]
	];

	NewLandscapeCategory.AddCustomRow(FText::GetEmpty())
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.FillWidth(1)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.Visibility_Static(&GetVisibilityOnlyInNewLandscapeMode, EUHLevelEditorNewLandscapeMethod::NewLandscape)
			.Text(LOCTEXT("Create", "Create"))
			.OnClicked(this, &FUHLevelEditorDetailCustomization_NewLandscape::OnCreateButtonClicked)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.Visibility_Static(&GetVisibilityOnlyInNewLandscapeMode, EUHLevelEditorNewLandscapeMethod::ImportLandscape)
			.Text(LOCTEXT("Import", "Import"))
			.OnClicked(this, &FUHLevelEditorDetailCustomization_NewLandscape::OnCreateButtonClicked)
			.IsEnabled(this, &FUHLevelEditorDetailCustomization_NewLandscape::GetImportButtonIsEnabled)
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<IDetailCustomization> FUHLevelEditorDetailCustomization_NewLandscape::MakeInstance()
{
	return MakeShareable(new FUHLevelEditorDetailCustomization_NewLandscape);
}

EVisibility FUHLevelEditorDetailCustomization_NewLandscape::GetVisibilityOnlyInNewLandscapeMode(EUHLevelEditorNewLandscapeMethod NewLandscapeMethod)
{
	checkSlow(NewLandscapeMethod != EUHLevelEditorNewLandscapeMethod::None);
	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		return (EdMode->UISettings->NewLandscapeMethod == NewLandscapeMethod) ? EVisibility::Visible : EVisibility::Collapsed;
	}
	return EVisibility::Collapsed;
}

ECheckBoxState FUHLevelEditorDetailCustomization_NewLandscape::NewLandscapeModeIsChecked(EUHLevelEditorNewLandscapeMethod NewLandscapeMethod) const
{
	checkSlow(NewLandscapeMethod != EUHLevelEditorNewLandscapeMethod::None);
	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		return (EdMode->UISettings->NewLandscapeMethod == NewLandscapeMethod) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
	}
	return ECheckBoxState::Unchecked;
}

void FUHLevelEditorDetailCustomization_NewLandscape::OnNewLandscapeModeChanged(ECheckBoxState NewCheckedState, EUHLevelEditorNewLandscapeMethod NewLandscapeMethod)
{
	checkSlow(NewLandscapeMethod != EUHLevelEditorNewLandscapeMethod::None);
	if (NewCheckedState == ECheckBoxState::Checked)
	{
		FUHLevelEditorEdMode* EdMode = GetEditorMode();
		if (EdMode)
		{
			EdMode->UISettings->NewLandscapeMethod = NewLandscapeMethod;
		}
	}
}

FReply FUHLevelEditorDetailCustomization_NewLandscape::OnCreateButtonClicked()
{
	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		
	}
	return FReply::Handled();
}

bool FUHLevelEditorDetailCustomization_NewLandscape::GetImportButtonIsEnabled() const
{
	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{

	}
	return false;
}

FText FUHLevelEditorDetailCustomization_NewLandscape::GetTotalComponentCount() const
{
	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		return FText::AsNumber(EdMode->UISettings->NewLandscape_ComponentCount.X * EdMode->UISettings->NewLandscape_ComponentCount.Y);
	}
	return FText::GetEmpty();
}

FText FUHLevelEditorDetailCustomization_NewLandscape::GetResolutionX() const
{
	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		return FText::AsNumber(EdMode->UISettings->NewLandscape_ComponentCount.X * EdMode->UISettings->NewLandscape_ComponentSize + 1);
	}
	return FText::GetEmpty();
}

FText FUHLevelEditorDetailCustomization_NewLandscape::GetResolutionY() const
{
	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		return FText::AsNumber(EdMode->UISettings->NewLandscape_ComponentCount.Y * EdMode->UISettings->NewLandscape_ComponentSize + 1);
	}
	return FText::GetEmpty();
}

#undef LOCTEXT_NAMESPACE