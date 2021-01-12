// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobaGameMode.h"
#include "Characters/Player/MobaPlayerController.h"
#include "Characters/Player/MobaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

/*
PlayAsClient 1
LogTemp: Warning: 1 AMobaGameMode NM_Standalone
LogTemp: Warning: 2 AMobaGameMode ROLE_Authority
LogTemp: Warning: 1  AMobaGameMode BeginPlay NM_DedicatedServer
LogTemp: Warning: 2 AMobaGameMode BeginPlay ROLE_Authority
PlayAsClient 2
LogTemp: Warning: 1 AMobaGameMode NM_Standalone
LogTemp: Warning: 2 AMobaGameMode ROLE_Authority
LogTemp: Warning: 1  AMobaGameMode BeginPlay NM_DedicatedServer
LogTemp: Warning: 2 AMobaGameMode BeginPlay ROLE_Authority
*/
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

void AMobaGameMode::BeginPlay()
{
	Super::BeginPlay();
}