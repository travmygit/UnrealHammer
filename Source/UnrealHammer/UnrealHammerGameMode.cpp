// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealHammerGameMode.h"
#include "UnrealHammerPlayerController.h"
#include "UnrealHammerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealHammerGameMode::AUnrealHammerGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUnrealHammerPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}