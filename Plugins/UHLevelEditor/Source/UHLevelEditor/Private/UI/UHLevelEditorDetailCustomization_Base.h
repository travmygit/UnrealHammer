// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/Casts.h"
#include "IDetailCustomization.h"
#include "PropertyHandle.h"

class FUHLevelEditorEdMode;
class IDetailLayoutBuilder;

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorDetailCustomization_Base

class FUHLevelEditorDetailCustomization_Base : public IDetailCustomization
{
public:
	//////////////////////////////////////////////////////////////////////////
	//~ Begin IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override = 0;
	//~ End IDetailCustomization interface
	//////////////////////////////////////////////////////////////////////////

protected:
	static FUHLevelEditorEdMode* GetEditorMode();
	static bool IsToolActive(FName ToolName);
	static bool IsBrushSetActive(FName BrushSetName);

	template<typename Type>
	static TOptional<Type> OnGetValue(TSharedRef<IPropertyHandle> PropertyHandle);

	template<typename Type>
	static void OnValueChanged(Type NewValue, TSharedRef<IPropertyHandle> PropertyHandle);

	template<typename Type>
	static void OnValueCommitted(Type NewValue, ETextCommit::Type CommitType, TSharedRef<IPropertyHandle> PropertyHandle);

	template<typename Type>
	static Type GetPropertyValue(TSharedRef<IPropertyHandle> PropertyHandle);

	template<typename Type>
	static TOptional<Type> GetOptionalPropertyValue(TSharedRef<IPropertyHandle> PropertyHandle);

	template<typename Type>
	static Type* GetObjectPropertyValue(TSharedRef<IPropertyHandle> PropertyHandle);

	static FText GetPropertyValueText(TSharedRef<IPropertyHandle> PropertyHandle);

	template<typename Type>
	static void SetPropertyValue(Type NewValue, ETextCommit::Type CommitInfo, TSharedRef<IPropertyHandle> PropertyHandle);
};

template<typename Type>
TOptional<Type> FUHLevelEditorDetailCustomization_Base::OnGetValue(TSharedRef<IPropertyHandle> PropertyHandle)
{
	Type Value;
	if (ensure(PropertyHandle->GetValue(Value) == FPropertyAccess::Success))
	{
		return TOptional<Type>(Value);
	}

	// Value couldn't be accessed. Return an unset value
	return TOptional<Type>();
}

template<typename Type>
void FUHLevelEditorDetailCustomization_Base::OnValueChanged(Type NewValue, TSharedRef<IPropertyHandle> PropertyHandle)
{
	const EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::InteractiveChange;
	ensure(PropertyHandle->SetValue(NewValue, Flags) == FPropertyAccess::Success);
}

template<typename Type>
void FUHLevelEditorDetailCustomization_Base::OnValueCommitted(Type NewValue, ETextCommit::Type CommitType, TSharedRef<IPropertyHandle> PropertyHandle)
{
	ensure(PropertyHandle->SetValue(NewValue) == FPropertyAccess::Success);
}

template<typename Type>
Type FUHLevelEditorDetailCustomization_Base::GetPropertyValue(TSharedRef<IPropertyHandle> PropertyHandle)
{
	Type Value;
	if (PropertyHandle->GetValue(Value) == FPropertyAccess::Success)
	{
		return Value;
	}

	// Couldn't get, return null / 0
	return Type{};
}

template<typename Type>
TOptional<Type> FUHLevelEditorDetailCustomization_Base::GetOptionalPropertyValue(TSharedRef<IPropertyHandle> PropertyHandle)
{
	Type Value;
	if (PropertyHandle->GetValue(Value) == FPropertyAccess::Success)
	{
		return Value;
	}

	// Couldn't get, return unset optional
	return TOptional<Type>();
}

template<typename Type>
Type* FUHLevelEditorDetailCustomization_Base::GetObjectPropertyValue(TSharedRef<IPropertyHandle> PropertyHandle)
{
	UObject* Value;
	if (PropertyHandle->GetValue(Value) == FPropertyAccess::Success)
	{
		return Cast<Type>(Value);
	}

	// Couldn't get, return null
	return nullptr;
}

inline FText FUHLevelEditorDetailCustomization_Base::GetPropertyValueText(TSharedRef<IPropertyHandle> PropertyHandle)
{
	FString Value;
	if (PropertyHandle->GetValueAsFormattedString(Value) == FPropertyAccess::Success)
	{
		return FText::FromString(Value);
	}

	return FText();
}

template<typename Type>
void FUHLevelEditorDetailCustomization_Base::SetPropertyValue(Type NewValue, ETextCommit::Type CommitInfo, TSharedRef<IPropertyHandle> PropertyHandle)
{
	ensure(PropertyHandle->SetValue(NewValue) == FPropertyAccess::Success);
}