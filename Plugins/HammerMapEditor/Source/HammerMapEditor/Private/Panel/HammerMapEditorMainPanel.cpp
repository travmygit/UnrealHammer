#include "Panel/HammerMapEditorMainPanel.h"

UHammerMapEditorMainPanel::UHammerMapEditorMainPanel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ...
}

bool UHammerMapEditorMainPanel::Initialize()
{
	const bool SuperInitialized = Super::Initialize();
	if (SuperInitialized)
	{
		// ...
	}
	return SuperInitialized;
}

void UHammerMapEditorMainPanel::BeginDestroy()
{
	// ...
	Super::BeginDestroy();
}
