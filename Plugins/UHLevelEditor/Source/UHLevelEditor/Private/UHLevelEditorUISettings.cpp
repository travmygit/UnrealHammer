#include "UHLevelEditorUISettings.h"
#include "UHLevelEditorEdMode.h"

UUHLevelEditorUISettings::UUHLevelEditorUISettings()
	: EdMode(nullptr)
{
	// NewLandscape
	NewLandscape_Location = FVector::ZeroVector;
	NewLandscape_Rotation = FRotator::ZeroRotator;
	NewLandscape_Scale = FVector(100.f);
	NewLandscape_ComponentSize = 7;
	NewLandscape_ComponentCount = FIntPoint(2);
}

void UUHLevelEditorUISettings::Init(FUHLevelEditorEdMode* InEdMode)
{
	EdMode = InEdMode;
}
