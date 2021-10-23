#pragma once

#include "CoreMinimal.h"
#include "Templates/Casts.h"
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"

class FUHLevelEditorEdMode;

/**
 * Slate widgets customizers for the UH Level Editor
 */
class FUHLevelEditorStructCustomization_Base : public IPropertyTypeCustomization
{
protected:
	static FUHLevelEditorEdMode* GetEditorMode();
};