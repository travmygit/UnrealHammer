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
#include "Widgets/Input/SVectorInputBox.h"
#include "Widgets/Input/SRotatorInputBox.h"

#define LOCTEXT_NAMESPACE "UHLevelEditor.NewLandscape"

const int32 FUHLevelEditorDetailCustomization_NewLandscape::ComponentSizes[6] = { 7, 15, 31, 63, 127, 255 };

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

	TSharedRef<IPropertyHandle> PropertyHandle_Location = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UUHLevelEditorUISettings, NewLandscape_Location));
	TSharedRef<IPropertyHandle> PropertyHandle_Location_X = PropertyHandle_Location->GetChildHandle("X").ToSharedRef();
	TSharedRef<IPropertyHandle> PropertyHandle_Location_Y = PropertyHandle_Location->GetChildHandle("Y").ToSharedRef();
	TSharedRef<IPropertyHandle> PropertyHandle_Location_Z = PropertyHandle_Location->GetChildHandle("Z").ToSharedRef();
	NewLandscapeCategory.AddProperty(PropertyHandle_Location)
	.CustomWidget()
	.NameContent()
	[
		PropertyHandle_Location->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(125.0f * 3.0f) // copied from FComponentTransformDetails
	.MaxDesiredWidth(125.0f * 3.0f)
	[
		SNew(SVectorInputBox)
		.bColorAxisLabels(true)
		.Font(DetailBuilder.GetDetailFont())
		.X_Static(&GetOptionalPropertyValue<float>, PropertyHandle_Location_X)
		.Y_Static(&GetOptionalPropertyValue<float>, PropertyHandle_Location_Y)
		.Z_Static(&GetOptionalPropertyValue<float>, PropertyHandle_Location_Z)
		.OnXCommitted_Static(&SetPropertyValue<float>, PropertyHandle_Location_X)
		.OnYCommitted_Static(&SetPropertyValue<float>, PropertyHandle_Location_Y)
		.OnZCommitted_Static(&SetPropertyValue<float>, PropertyHandle_Location_Z)
		.OnXChanged_Lambda([=](float NewValue) { ensure(PropertyHandle_Location_X->SetValue(NewValue, EPropertyValueSetFlags::InteractiveChange) == FPropertyAccess::Success); })
		.OnYChanged_Lambda([=](float NewValue) { ensure(PropertyHandle_Location_Y->SetValue(NewValue, EPropertyValueSetFlags::InteractiveChange) == FPropertyAccess::Success); })
		.OnZChanged_Lambda([=](float NewValue) { ensure(PropertyHandle_Location_Z->SetValue(NewValue, EPropertyValueSetFlags::InteractiveChange) == FPropertyAccess::Success); })
		.AllowSpin(true)
	];

	TSharedRef<IPropertyHandle> PropertyHandle_Rotation = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UUHLevelEditorUISettings, NewLandscape_Rotation));
	TSharedRef<IPropertyHandle> PropertyHandle_Rotation_Roll  = PropertyHandle_Rotation->GetChildHandle("Roll").ToSharedRef();
	TSharedRef<IPropertyHandle> PropertyHandle_Rotation_Pitch = PropertyHandle_Rotation->GetChildHandle("Pitch").ToSharedRef();
	TSharedRef<IPropertyHandle> PropertyHandle_Rotation_Yaw   = PropertyHandle_Rotation->GetChildHandle("Yaw").ToSharedRef();
	NewLandscapeCategory.AddProperty(PropertyHandle_Rotation)
	.CustomWidget()
	.NameContent()
	[
		PropertyHandle_Rotation->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(125.0f * 3.0f) // copied from FComponentTransformDetails
	.MaxDesiredWidth(125.0f * 3.0f)
	[
		SNew(SRotatorInputBox)
		.bColorAxisLabels(true)
		.AllowResponsiveLayout(true)
		.Font(DetailBuilder.GetDetailFont())
		.Roll_Static(&GetOptionalPropertyValue<float>, PropertyHandle_Rotation_Roll)
		.Pitch_Static(&GetOptionalPropertyValue<float>, PropertyHandle_Rotation_Pitch)
		.Yaw_Static(&GetOptionalPropertyValue<float>, PropertyHandle_Rotation_Yaw)
		.OnYawCommitted_Static(&SetPropertyValue<float>, PropertyHandle_Rotation_Yaw) // not allowed to roll or pitch landscape
		.OnYawChanged_Lambda([=](float NewValue){ ensure(PropertyHandle_Rotation_Yaw->SetValue(NewValue, EPropertyValueSetFlags::InteractiveChange) == FPropertyAccess::Success); })
		.AllowSpin(true)
	];

	TSharedRef<IPropertyHandle> PropertyHandle_Scale = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UUHLevelEditorUISettings, NewLandscape_Scale));
	TSharedRef<IPropertyHandle> PropertyHandle_Scale_X = PropertyHandle_Scale->GetChildHandle("X").ToSharedRef();
	TSharedRef<IPropertyHandle> PropertyHandle_Scale_Y = PropertyHandle_Scale->GetChildHandle("Y").ToSharedRef();
	TSharedRef<IPropertyHandle> PropertyHandle_Scale_Z = PropertyHandle_Scale->GetChildHandle("Z").ToSharedRef();
	NewLandscapeCategory.AddProperty(PropertyHandle_Scale)
	.CustomWidget()
	.NameContent()
	[
		SNew(SBox)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Font(DetailBuilder.GetDetailFont())
			.Text(LOCTEXT("QuadSize", "Quad Size"))
		]
		//PropertyHandle_Scale->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(125.0f * 3.0f) // copied from FComponentTransformDetails
	.MaxDesiredWidth(125.0f * 3.0f)
	[
		SNew(SVectorInputBox)
		.bColorAxisLabels(true)
		.Font(DetailBuilder.GetDetailFont())
		.X_Static(&GetOptionalPropertyValue<float>, PropertyHandle_Scale_X)
		.Y_Static(&GetOptionalPropertyValue<float>, PropertyHandle_Scale_Y)
		.Z_Static(&GetOptionalPropertyValue<float>, PropertyHandle_Scale_Z)
		//.OnXCommitted_Static(&SetScale, PropertyHandle_Scale_X) // not allowed to resize quad
		//.OnYCommitted_Static(&SetScale, PropertyHandle_Scale_Y)
		//.OnZCommitted_Static(&SetScale, PropertyHandle_Scale_Z)
		//.OnXChanged_Lambda([=](float NewValue) { ensure(PropertyHandle_Scale_X->SetValue(NewValue, EPropertyValueSetFlags::InteractiveChange) == FPropertyAccess::Success); })
		//.OnYChanged_Lambda([=](float NewValue) { ensure(PropertyHandle_Scale_Y->SetValue(NewValue, EPropertyValueSetFlags::InteractiveChange) == FPropertyAccess::Success); })
		//.OnZChanged_Lambda([=](float NewValue) { ensure(PropertyHandle_Scale_Z->SetValue(NewValue, EPropertyValueSetFlags::InteractiveChange) == FPropertyAccess::Success); })
		.AllowSpin(true)
	];

	TSharedRef<IPropertyHandle> PropertyHandle_ComponentSize = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UUHLevelEditorUISettings, NewLandscape_ComponentSize));
	NewLandscapeCategory.AddProperty(PropertyHandle_ComponentSize)
	.CustomWidget()
	.NameContent()
	[
		PropertyHandle_ComponentSize->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		SNew(SComboButton)
		.OnGetMenuContent_Static(&GetComponentSizeMenu, PropertyHandle_ComponentSize)
		.ContentPadding(2)
		.ButtonContent()
		[
			SNew(STextBlock)
			.Font(DetailBuilder.GetDetailFont())
			.Text_Static(&GetComponentSize, PropertyHandle_ComponentSize)
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

TSharedRef<SWidget> FUHLevelEditorDetailCustomization_NewLandscape::GetComponentSizeMenu(TSharedRef<IPropertyHandle> PropertyHandle)
{
	FMenuBuilder MenuBuilder(true, nullptr);

	for (int32 Idx = 0; Idx < UE_ARRAY_COUNT(ComponentSizes); Idx++)
	{
		MenuBuilder.AddMenuEntry(FText::Format(LOCTEXT("NxNQuads", "{0}\u00D7{0} Quads"), FText::AsNumber(ComponentSizes[Idx])), FText::GetEmpty(),
			FSlateIcon(), FExecuteAction::CreateStatic(&OnComponentSizeChanged, PropertyHandle, ComponentSizes[Idx]));
	}

	return MenuBuilder.MakeWidget();
}

void FUHLevelEditorDetailCustomization_NewLandscape::OnComponentSizeChanged(TSharedRef<IPropertyHandle> PropertyHandle, int32 NewSize)
{
	ensure(PropertyHandle->SetValue(NewSize) == FPropertyAccess::Success);
}

FText FUHLevelEditorDetailCustomization_NewLandscape::GetComponentSize(TSharedRef<IPropertyHandle> PropertyHandle)
{
	int32 ComponentSize = 0;
	FPropertyAccess::Result Result = PropertyHandle->GetValue(ComponentSize);
	checkSlow(Result == FPropertyAccess::Success);
	if (Result == FPropertyAccess::MultipleValues)
	{
		return LOCTEXT("MultipleValues", "Multiple Values");
	}
	return FText::Format(LOCTEXT("NxNQuads", "{0}\u00D7{0} Quads"), FText::AsNumber(ComponentSize));
}

void FUHLevelEditorDetailCustomization_NewLandscape::SetScale(float NewValue, ETextCommit::Type, TSharedRef<IPropertyHandle> PropertyHandle)
{
	float OldValue = 0;
	PropertyHandle->GetValue(OldValue);

	if (NewValue == 0)
	{
		if (OldValue < 0)
		{
			NewValue = -1;
		}
		else
		{
			NewValue = 1;
		}
	}

	ensure(PropertyHandle->SetValue(NewValue) == FPropertyAccess::Success);

	// Make X and Y scale match
	FName PropertyName = PropertyHandle->GetProperty()->GetFName();
	if (PropertyName == "X")
	{
		TSharedRef<IPropertyHandle> PropertyHandle_Y = PropertyHandle->GetParentHandle()->GetChildHandle("Y").ToSharedRef();
		ensure(PropertyHandle_Y->SetValue(NewValue) == FPropertyAccess::Success);
	}
	else if (PropertyName == "Y")
	{
		TSharedRef<IPropertyHandle> PropertyHandle_X = PropertyHandle->GetParentHandle()->GetChildHandle("X").ToSharedRef();
		ensure(PropertyHandle_X->SetValue(NewValue) == FPropertyAccess::Success);
	}
}

#undef LOCTEXT_NAMESPACE