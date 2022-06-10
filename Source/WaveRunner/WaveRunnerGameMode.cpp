// Copyright Epic Games, Inc. All Rights Reserved.

#include "WaveRunnerGameMode.h"
#include "WaveRunnerCharacter.h"

AWaveRunnerGameMode::AWaveRunnerGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AWaveRunnerCharacter::StaticClass();	
}
