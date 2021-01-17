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

	// remove the default camera actor in the level as it is not used at all
	//TArray<AActor*> CameraActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);
	//for (AActor* CameraActor : CameraActors)
	//{
	//	if (CameraActor->GetName().Contains(TEXT("CameraActor")))
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("AMobaGameMode::BeginPlay() Removed camera %s"), *CameraActor->GetName()));
	//		UE_LOG(LogTemp, Warning, TEXT(" AMobaGameMode::BeginPlay() Removed default camera %s"), *(CameraActor->GetName()));
	//		check(CameraActor->Destroy());
	//	}
	//}

	//if (GetNetMode() != NM_DedicatedServer && GetWorld()->GetFirstPlayerController())
	//{
	//	ShowNetModeAndRole(" AMobaGameMode::BeginPlay()", true);
	//	// Only spawn camera in client/listenserver mode
	//	TArray<AActor*> PlayerStartActor;
	//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActor);
	//	check(PlayerStartActor.Num() == 1);
	//	auto CameraPawn = GetWorld()->SpawnActorDeferred<ACameraPawn>(ACameraPawn::StaticClass(), FTransform::Identity, this);
	//	CameraPawn->SetReplicates(false);
	//	CameraPawn->bNetLoadOnClient = false;
	//	CameraPawn->SetReplicatingMovement(false);
	//	CameraPawn->bAlwaysRelevant = false;
	//	CameraPawn->bRelevantForNetworkReplays = false;
	//	CameraPawn->bReplayRewindable = false;
	//	CameraPawn->FinishSpawning(FTransform::Identity, true);
	//	CameraPawn->SetActorLocation(PlayerStartActor[0]->GetActorLocation());
	//	(Cast<AMobaPlayerController>(GetWorld()->GetFirstPlayerController()))->CameraPawn = CameraPawn;
	//	GetWorld()->GetFirstPlayerController()->SetViewTarget(CameraPawn);
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("AMobaGameMode::BeginPlay() Spawn camera %s"), *CameraPawn->GetName()));
	//	UE_LOG(LogTemp, Warning, TEXT("AMobaGameMode::BeginPlay() Spawn camera %s"), *(CameraPawn->GetName()));
	//}
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