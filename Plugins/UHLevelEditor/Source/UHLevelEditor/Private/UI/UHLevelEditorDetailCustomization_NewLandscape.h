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
};