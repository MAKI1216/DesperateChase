// Copyright Epic Games, Inc. All Rights Reserved.

#include "DesperateChaseGameMode.h"
#include "DesperateChaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADesperateChaseGameMode::ADesperateChaseGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
