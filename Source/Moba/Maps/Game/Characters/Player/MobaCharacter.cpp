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
	 if (GetNetMode() != NM_DedicatedServer)
	 {
		 AMobaPlayerController* MobaPlayerController = Cast<AMobaPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		 if (!MobaPlayerController->bCameraInited)
		 {
			 MobaPlayerController->InitCamera(GetActorTransform().GetLocation());
		 }
	 }

	/* if (GetNetMode() == NM_Client)
	 {
		 GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  AMobaCharacter BeginPlay NM_Client");
		 UE_LOG(LogTemp, Warning, TEXT("1  AMobaCharacter BeginPlay NM_Client"));
	 }
	 if (GetNetMode() == NM_DedicatedServer)
	 {
		 GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  AMobaCharacter BeginPlay NM_DedicatedServer");
		 UE_LOG(LogTemp, Warning, TEXT("1  AMobaCharacter BeginPlay NM_DedicatedServer"));
	 }
	 if (GetNetMode() == NM_Standalone)
	 {
		 GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 AMobaCharacter BeginPlay NM_Standalone");
		 UE_LOG(LogTemp, Warning, TEXT("1 AMobaCharacter BeginPlay NM_Standalone"));
	 }
	 if (GetNetMode() == NM_ListenServer)
	 {
		 GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 AMobaCharacter BeginPlay NM_ListenServer");
		 UE_LOG(LogTemp, Warning, TEXT("1 AMobaCharacter BeginPlay NM_ListenServer"));
	 }
	 if (GetLocalRole() == ROLE_AutonomousProxy)
	 {
		 GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2  AMobaCharacter ROLE_AutonomousProxy");
		 UE_LOG(LogTemp, Warning, TEXT("2  AMobaCharacter BeginPlay ROLE_AutonomousProxy"));
	 }
	 if (GetLocalRole() == ROLE_Authority)
	 {
		 GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 AMobaCharacter BeginPlay ROLE_Authority");
		 UE_LOG(LogTemp, Warning, TEXT("2 AMobaCharacter BeginPlay ROLE_Authority"));
	 }
	 if (GetLocalRole() == ROLE_SimulatedProxy)
	 {
		 GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 AMobaCharacter BeginPlay ROLE_SimulatedProxy");
		 UE_LOG(LogTemp, Warning, TEXT("2 AMobaCharacter BeginPlay ROLE_SimulatedProxy"));
	 }*/
}

void AMobaCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
