// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "MobaPlayerController.h"
#include "Engine/World.h"
#include "Math/Vector.h"

/*
PlayAsListenServer 2
LogTemp: Warning: 1 AMobaCharacter BeginPlay NM_ListenServer
LogTemp: Warning: 2 AMobaCharacter BeginPlay ROLE_Authority
LogTemp: Warning: 1 AMobaCharacter BeginPlay NM_ListenServer
LogTemp: Warning: 2 AMobaCharacter BeginPlay ROLE_Authority
LogTemp: Warning: 1  AMobaCharacter BeginPlay NM_Client
LogTemp: Warning: 2  AMobaCharacter BeginPlay ROLE_AutonomousProxy
LogTemp: Warning: 1  AMobaCharacter BeginPlay NM_Client
LogTemp: Warning: 2 AMobaCharacter BeginPlay ROLE_SimulatedProxy
*/
AMobaCharacter::AMobaCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	previousMovementVector = GetActorLocation();

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

 void AMobaCharacter::BeginPlay()
{
	 Super::BeginPlay();
	 //ShowNetModeAndRole("AMobaPlayerController::BeginPlay");
}

void AMobaCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AMobaCharacter::ShowNetModeAndRole(const FString& str, bool bOnScreenMsg)
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
