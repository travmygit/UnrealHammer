#include "Panel/HammerMapEditorPanelBase.h"

UHammerMapEditorPanelBase::UHammerMapEditorPanelBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ...
}

bool UHammerMapEditorPanelBase::Initialize()
{
	const bool SuperInitialized = Super::Initialize();
	if (SuperInitialized)
	{
		// ...
	}
	return SuperInitialized;
}

void UHammerMapEditorPanelBase::BeginDestroy()
{
	// ...
	Super::BeginDestroy();
}
