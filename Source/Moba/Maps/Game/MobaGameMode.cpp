// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobaGameMode.h"
#include "Characters/Player/MobaPlayerController.h"
#include "Characters/Player/MobaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Characters/Player/CameraPawn.h"

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

void AMobaGameMode::ShowNetModeAndRole(const FString& str, bool bOnScreenMsg)
{
	if (GetNetMode() == NM_Client)
	{
		if (bOnScreenMsg) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 " + str + " NM_Client");
		UE_LOG(LogTemp, Warning, TEXT("1 %s NM_Client"), *str);
	}
	if (GetNetMode() == NM_DedicatedServer)
	{
		if (bOnScreenMsg) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 " + str + " NM_DedicatedServer");
		UE_LOG(LogTemp, Warning, TEXT("1 %s NM_DedicatedServer"), *str);
	}
	if (GetNetMode() == NM_Standalone)
	{
		if (bOnScreenMsg) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 " + str + " NM_Standalone");
		UE_LOG(LogTemp, Warning, TEXT("1 %s NM_Standalone"), *str);
	}
	if (GetNetMode() == NM_ListenServer)
	{
		if (bOnScreenMsg) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 " + str + " NM_ListenServer");
		UE_LOG(LogTemp, Warning, TEXT("1 %s NM_ListenServer"), *str);
	}
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		if (bOnScreenMsg) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2  " + str + " ROLE_AutonomousProxy");
		UE_LOG(LogTemp, Warning, TEXT("2  %s ROLE_AutonomousProxy"), *str);
	}
	if (GetLocalRole() == ROLE_Authority)
	{
		if (bOnScreenMsg) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 " + str + " ROLE_Authority");
		UE_LOG(LogTemp, Warning, TEXT("2 %s ROLE_Authority"), *str);
	}
	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		if (bOnScreenMsg) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 " + str + " ROLE_SimulatedProxy");
		UE_LOG(LogTemp, Warning, TEXT("2 %s ROLE_SimulatedProxy"), *str);
	}
}