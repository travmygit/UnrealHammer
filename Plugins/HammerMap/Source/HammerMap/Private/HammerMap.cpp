// Copyright Epic Games, Inc. All Rights Reserved.

#include "HammerMap.h"

#define LOCTEXT_NAMESPACE "FHammerMapModule"

void FHammerMapModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FHammerMapModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHammerMapModule, HammerMap)