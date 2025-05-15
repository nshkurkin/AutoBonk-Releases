// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerDemoGameMode.h"
#include "MultiplayerDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayerDemoGameMode::AMultiplayerDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
