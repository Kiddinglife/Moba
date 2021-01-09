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

	/*if (GetNetMode() == NM_Client)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  AMobaGameMode NM_Client");
		UE_LOG(LogTemp, Warning, TEXT("1  AMobaGameMode NM_Client"));
	}
	if (GetNetMode() == NM_DedicatedServer)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  AMobaGameMode NM_DedicatedServer");
		UE_LOG(LogTemp, Warning, TEXT("1  AMobaGameMode NM_DedicatedServer"));
	}
	if (GetNetMode() == NM_Standalone)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 AMobaGameMode NM_Standalone");
		UE_LOG(LogTemp, Warning, TEXT("1 AMobaGameMode NM_Standalone"));
	}
	if (GetNetMode() == NM_ListenServer)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 AMobaGameMode NM_ListenServer");
		UE_LOG(LogTemp, Warning, TEXT("1 AMobaGameMode NM_ListenServer"));
	}
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2  AMobaGameMode ROLE_AutonomousProxy");
		UE_LOG(LogTemp, Warning, TEXT("2  AMobaGameMode ROLE_AutonomousProxy"));
	}
	if (GetLocalRole() == ROLE_Authority)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 AMobaGameMode ROLE_Authority");
		UE_LOG(LogTemp, Warning, TEXT("2 AMobaGameMode ROLE_Authority"));
	}
	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 AMobaGameMode ROLE_SimulatedProxy");
		UE_LOG(LogTemp, Warning, TEXT("2 AMobaGameMode ROLE_SimulatedProxy"));
	}*/
}

void AMobaGameMode::BeginPlay()
{
	Super::BeginPlay();

	// remove the default camera actor in the level as it is not used at all
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);
	for (AActor* CameraActor : CameraActors)
	{
		if (CameraActor->GetName().Contains(TEXT("CameraActor")))
		{
			FString Msg = FString::Printf(TEXT("AMobaGameMode::BeginPlay Removed default camera %s"), *(CameraActor->GetName()));
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Msg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
			check(CameraActor->Destroy());
		}
	}

	/*if (GetNetMode() == NM_Client)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  AMobaGameMode BeginPlay NM_Client");
		UE_LOG(LogTemp, Warning, TEXT("1  AMobaGameMode BeginPlay NM_Client"));
	}
	if (GetNetMode() == NM_DedicatedServer)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  AMobaGameMode BeginPlay NM_DedicatedServer");
		UE_LOG(LogTemp, Warning, TEXT("1  AMobaGameMode BeginPlay NM_DedicatedServer"));
	}
	if (GetNetMode() == NM_Standalone)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 AMobaGameMode BeginPlay NM_Standalone");
		UE_LOG(LogTemp, Warning, TEXT("1 AMobaGameMode BeginPlay NM_Standalone"));
	}
	if (GetNetMode() == NM_ListenServer)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 AMobaGameMode BeginPlay NM_ListenServer");
		UE_LOG(LogTemp, Warning, TEXT("1 AMobaGameMode BeginPlay NM_ListenServer"));
	}
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2  AMobaGameMode BeginPlay ROLE_AutonomousProxy");
		UE_LOG(LogTemp, Warning, TEXT("2  AMobaGameMode BeginPlay ROLE_AutonomousProxy"));
	}
	if (GetLocalRole() == ROLE_Authority)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 AMobaGameMode BeginPlay ROLE_Authority");
		UE_LOG(LogTemp, Warning, TEXT("2 AMobaGameMode BeginPlay ROLE_Authority"));
	}
	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 AMobaGameMode BeginPlay ROLE_SimulatedProxy");
		UE_LOG(LogTemp, Warning, TEXT("2 AMobaGameMode BeginPlay ROLE_SimulatedProxy"));
	}*/
}