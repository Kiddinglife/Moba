// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobaPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MobaCharacter.h"
#include "Engine/World.h"
#include "CameraPawn.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

/*
PlayAsClient 1
LogTemp: Warning: 1  AMobaPlayerController NM_DedicatedServer
LogTemp: Warning: 2 AMobaPlayerController ROLE_Authority
LogTemp: Warning: 1  AMobaPlayerController BeginPlay NM_DedicatedServer
LogTemp: Warning: 2 AMobaPlayerController BeginPlay ROLE_Authority
LogTemp: Warning: 1  AMobaPlayerController NM_Client
LogTemp: Warning: 2 AMobaPlayerController ROLE_Authority
LogTemp: Warning: 1  AMobaPlayerController BeginPlay NM_Client
LogTemp: Warning: 2  AMobaPlayerController BeginPlay ROLE_AutonomousProxy

PlayAsClient 2
LogTemp: Warning: 1  AMobaPlayerController NM_DedicatedServer
LogTemp: Warning: 2 AMobaPlayerController ROLE_Authority
LogTemp: Warning: 1  AMobaPlayerController BeginPlay NM_DedicatedServer
LogTemp: Warning: 2 AMobaPlayerController BeginPlay ROLE_Authority
LogTemp: Warning: 1  AMobaPlayerController NM_Client
LogTemp: Warning: 2 AMobaPlayerController ROLE_Authority
LogTemp: Warning: 1  AMobaPlayerController BeginPlay NM_Client
LogTemp: Warning: 2  AMobaPlayerController BeginPlay ROLE_AutonomousProxy

LogTemp: Warning: 1  AMobaPlayerController NM_DedicatedServer
LogTemp: Warning: 2 AMobaPlayerController ROLE_Authority
LogTemp: Warning: 1  AMobaPlayerController BeginPlay NM_DedicatedServer
LogTemp: Warning: 2 AMobaPlayerController BeginPlay ROLE_Authority
LogTemp: Warning: 1  AMobaPlayerController NM_Client
LogTemp: Warning: 2 AMobaPlayerController ROLE_Authority
LogTemp: Warning: 1  AMobaPlayerController BeginPlay NM_Client
LogTemp: Warning: 2  AMobaPlayerController BeginPlay ROLE_AutonomousProxy

PlayAsListenServer 1
LogTemp: Warning: 1 AMobaPlayerController NM_Standalone
LogTemp: Warning: 2 AMobaPlayerController ROLE_Authority
LogTemp: Warning: 1 AMobaPlayerController BeginPlay NM_ListenServer
LogTemp: Warning: 2 AMobaPlayerController BeginPlay ROLE_Authority

PlayAsListenServer 2
LogTemp: Warning: 1 AMobaPlayerController NM_Standalone
LogTemp: Warning: 2 AMobaPlayerController ROLE_Authority
LogTemp: Warning: 1 AMobaPlayerController BeginPlay NM_ListenServer
LogTemp: Warning: 2 AMobaPlayerController BeginPlay ROLE_Authority

LogTemp: Warning: 1 AMobaPlayerController NM_ListenServer
LogTemp: Warning: 2 AMobaPlayerController ROLE_Authority
LogTemp: Warning: 1 AMobaPlayerController BeginPlay NM_ListenServer
LogTemp: Warning: 2 AMobaPlayerController BeginPlay ROLE_Authority

LogTemp: Warning: 1  AMobaPlayerController NM_Client
LogTemp: Warning: 2 AMobaPlayerController ROLE_Authority
LogTemp: Warning: 1  AMobaPlayerController BeginPlay NM_Client
LogTemp: Warning: 2  AMobaPlayerController BeginPlay ROLE_AutonomousProxy
*/
AMobaPlayerController::AMobaPlayerController()
{
#if WITH_SERVER_CODE
#endif
	CameraPawn = nullptr;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bAutoManageActiveCameraTarget = false;
	bCameraInited = false;
	//if (GetNetMode() == NM_Client)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  AMobaPlayerController NM_Client");
	//	UE_LOG(LogTemp, Warning, TEXT("1  AMobaPlayerController NM_Client"));
	//}
	//if (GetNetMode() == NM_DedicatedServer)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  AMobaPlayerController NM_DedicatedServer");
	//	UE_LOG(LogTemp, Warning, TEXT("1  AMobaPlayerController NM_DedicatedServer"));
	//}
	//if (GetNetMode() == NM_Standalone)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 AMobaPlayerController NM_Standalone");
	//	UE_LOG(LogTemp, Warning, TEXT("1 AMobaPlayerController NM_Standalone"));
	//}
	//if (GetNetMode() == NM_ListenServer)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 AMobaPlayerController NM_ListenServer");
	//	UE_LOG(LogTemp, Warning, TEXT("1 AMobaPlayerController NM_ListenServer"));
	//}
	//if (GetLocalRole() == ROLE_AutonomousProxy)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2  AMobaPlayerController ROLE_AutonomousProxy");
	//	UE_LOG(LogTemp, Warning, TEXT("2  AMobaPlayerController ROLE_AutonomousProxy"));
	//}
	//if (GetLocalRole() == ROLE_Authority)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 AMobaPlayerController ROLE_Authority");
	//	UE_LOG(LogTemp, Warning, TEXT("2 AMobaPlayerController ROLE_Authority"));
	//}
	//if (GetLocalRole() == ROLE_SimulatedProxy)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 AMobaPlayerController ROLE_SimulatedProxy");
	//	UE_LOG(LogTemp, Warning, TEXT("2 AMobaPlayerController ROLE_SimulatedProxy"));
	//}
}

void AMobaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitCamera();
	//ShowNetModeAndRole("AMobaPlayerController BeginPlay");
}

void AMobaPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMobaPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	/*if (GetNetMode() == NM_Client)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  NM_Client");
	}
	if (GetNetMode() == NM_DedicatedServer)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  NM_DedicatedServer");
	}
	if (GetNetMode() == NM_Standalone)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 NM_Standalone");
	}
	if (GetNetMode() == NM_ListenServer)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 NM_ListenServer");
	}
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2  ROLE_AutonomousProxy");
	}
	if (GetLocalRole() == ROLE_Authority)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 ROLE_Authority");
	}
	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 ROLE_SimulatedProxy");
	}*/
	
	if (CameraPawn)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		//CameraPawn->SetActorLocation(GetPawn()->GetActorTransform().GetLocation());
		CameraPawn->GetCursorToWorld()->SetWorldLocation(Hit.Location);
		CameraPawn->GetCursorToWorld()->SetWorldRotation(Hit.ImpactNormal.Rotation());
		// keep updating the destination every tick while desired
		if (bMoveToMouseCursor)
		{
			MoveToMouseCursor(Hit);
		}
	}
}

void AMobaPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMobaPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMobaPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMobaPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMobaPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AMobaPlayerController::OnResetVR);
}

void AMobaPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMobaPlayerController::MoveToMouseCursor(const FHitResult& Hit)
{
	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AMobaPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AMobaPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	AMobaCharacter* const MyPawn = Cast<AMobaCharacter>(GetPawn());
	float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());
	// We need to issue move command only if far enough in order for walk animation to play correctly
	if ((Distance > 120.0f))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
	}
}

void AMobaPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "OnSetDestinationPressed");
	//ShowNetModeAndRole("AMobaPlayerController::OnSetDestinationPressed");
	//if (GetPawn())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT(" AMobaPlayerController::InitCamera() GetPawn()->GetName() %s"), *(GetPawn()->GetName()));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT(" AMobaPlayerController::InitCamera() GetPawn()->GetName() NOT EXIST"));
	//}
}

void AMobaPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

//void AMobaPlayerController::InitCamera(const FVector& t)
//{
//	if (CameraPawn)
//	{
//		CameraPawn->SetActorLocation(t);
//		bCameraInited = true;
//	}
//}

void AMobaPlayerController::InitCamera()
{
	// remove the default camera actor in the level as it is not used at all
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);
	for (AActor* CameraActor : CameraActors)
	{
		if (CameraActor->GetName().Contains(TEXT("CameraActor")))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, CameraActor->GetName());
			UE_LOG(LogTemp, Warning, TEXT(" AMobaPlayerController::InitCamera() Removed default camera %s"), *(CameraActor->GetName()));
			check(CameraActor->Destroy());
		}
	}

	// Only spawn camera in client/listenserver mode
	if (GetNetMode() != NM_DedicatedServer)
	{
		TArray<AActor*> PlayerStartActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActor);
		check(PlayerStartActor.Num() == 1);
		//CameraPawn = GetWorld()->SpawnActor<ACameraPawn>(ACameraPawn::StaticClass(), GetPawn()->GetActorTransform());
		CameraPawn = GetWorld()->SpawnActor<ACameraPawn>(ACameraPawn::StaticClass());
		CameraPawn->SetActorLocation(PlayerStartActor[0]->GetActorLocation());
		//FTransform Transform;
		//Transform.SetRotation(FQuat::MakeFromEuler({0.000042, -50.597729, 0.595521}));
		//Transform.SetLocation({ -1379.584351, 7.022931, 947.442017 });
		//CameraPawn = GetWorld()->SpawnActor<ACameraPawn>(ACameraPawn::StaticClass(), Transform);
		SetViewTarget(CameraPawn);
	}
}

void AMobaPlayerController::ShowNetModeAndRole(const FString& str, bool bOnScreenMsg)
{
	if (GetNetMode() == NM_Client)
	{
		if(bOnScreenMsg) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 " + str + " NM_Client");
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
		if (bOnScreenMsg) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2  "+ str + " ROLE_AutonomousProxy");
		UE_LOG(LogTemp, Warning, TEXT("2  %s ROLE_AutonomousProxy"), *str);
	}
	if (GetLocalRole() == ROLE_Authority)
	{
		if (bOnScreenMsg) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 " + str + " ROLE_Authority");
		UE_LOG(LogTemp, Warning, TEXT("2 %s ROLE_Authority"), *str);
	}
	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		if (bOnScreenMsg) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 "+str+" ROLE_SimulatedProxy");
		UE_LOG(LogTemp, Warning, TEXT("2 %s ROLE_SimulatedProxy"), *str);
	}
}

void AMobaPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//ShowNetModeAndRole("AMobaPlayerController::OnPossess");
	//UE_LOG(LogTemp, Warning, TEXT("InPawn name: %s"), *(InPawn->GetName()));
}
