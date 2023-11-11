// Copyright Epic Games, Inc. All Rights Reserved.

#include "BallsGameMode.h"
#include "BallsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABallsGameMode::ABallsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
