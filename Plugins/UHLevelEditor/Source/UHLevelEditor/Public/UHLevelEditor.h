// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FUHLevelEditorModule : public IModuleInterface
{
public:

	//////////////////////////////////////////////////////////////////////////
	//~ Begin IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~ End IModuleInterface interface
	//////////////////////////////////////////////////////////////////////////
};
