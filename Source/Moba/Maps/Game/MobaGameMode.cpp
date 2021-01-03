// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobaGameMode.h"
#include "Characters/Player/MobaPlayerController.h"
#include "Characters/Player/MobaCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMobaGameMode::AMobaGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMobaPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/Moba/Maps/Game/Characters/Player/TopDownCharacter'"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}