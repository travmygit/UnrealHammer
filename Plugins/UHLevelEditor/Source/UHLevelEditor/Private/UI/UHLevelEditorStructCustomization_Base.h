// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/Casts.h"
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"

class FUHLevelEditorEdMode;

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorStructCustomization_Base

class FUHLevelEditorStructCustomization_Base : public IPropertyTypeCustomization
{
protected:
	static FUHLevelEditorEdMode* GetEditorMode();
};