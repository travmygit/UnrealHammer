// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/Casts.h"
#include "IDetailCustomization.h"
#include "PropertyHandle.h"
#include "UHLevelEditorEdMode.h"
#include "UI/UHLevelEditorUISettings.h"
#include "UI/UHLevelEditorDetailCustomization_Base.h"

class FUHLevelEditorEdMode;
class IDetailLayoutBuilder;

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorDetailCustomization_NewLandscape

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

	static EVisibility GetVisibilityOnlyInNewLandscapeMode(EUHLevelEditorNewLandscapeMethod NewLandscapeMethod);
	ECheckBoxState NewLandscapeModeIsChecked(EUHLevelEditorNewLandscapeMethod NewLandscapeMethod) const;
	void OnNewLandscapeModeChanged(ECheckBoxState NewCheckedState, EUHLevelEditorNewLandscapeMethod NewLandscapeMethod);

	FReply OnCreateButtonClicked();
	bool GetImportButtonIsEnabled() const;

	FText GetTotalComponentCount() const;
	FText GetResolutionX() const;
	FText GetResolutionY() const;

	static TSharedRef<SWidget> GetComponentSizeMenu(TSharedRef<IPropertyHandle> PropertyHandle);
	static void OnComponentSizeChanged(TSharedRef<IPropertyHandle> PropertyHandle, int32 NewSize);
	static FText GetComponentSize(TSharedRef<IPropertyHandle> PropertyHandle);
	static const int32 ComponentSizes[6];

	static void SetScale(float NewValue, ETextCommit::Type, TSharedRef<IPropertyHandle> PropertyHandle);
};