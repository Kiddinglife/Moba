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

	if (GetNetMode() == NM_Client)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  AMobaPlayerController BeginPlay NM_Client");
		UE_LOG(LogTemp, Warning, TEXT("1  AMobaPlayerController BeginPlay NM_Client"));
	}
	if (GetNetMode() == NM_DedicatedServer)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  AMobaPlayerController BeginPlay NM_DedicatedServer");
		UE_LOG(LogTemp, Warning, TEXT("1  AMobaPlayerController BeginPlay NM_DedicatedServer"));
	}
	if (GetNetMode() == NM_Standalone)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 AMobaPlayerController BeginPlay NM_Standalone");
		UE_LOG(LogTemp, Warning, TEXT("1 AMobaPlayerController BeginPlay NM_Standalone"));
	}
	if (GetNetMode() == NM_ListenServer)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 AMobaPlayerController BeginPlay NM_ListenServer");
		UE_LOG(LogTemp, Warning, TEXT("1 AMobaPlayerController BeginPlay NM_ListenServer"));
	}
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2  AMobaPlayerControllerBeginPlay ROLE_AutonomousProxy");
		UE_LOG(LogTemp, Warning, TEXT("2  AMobaPlayerController BeginPlay ROLE_AutonomousProxy"));
	}
	if (GetLocalRole() == ROLE_Authority)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 AMobaPlayerController BeginPlay ROLE_Authority");
		UE_LOG(LogTemp, Warning, TEXT("2 AMobaPlayerController BeginPlay ROLE_Authority"));
	}
	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 AMobaPlayerController BeginPlay ROLE_SimulatedProxy");
		UE_LOG(LogTemp, Warning, TEXT("2 AMobaPlayerController BeginPlay ROLE_SimulatedProxy"));
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);
	for (AActor* poCameraActor : FoundActors)
	{
		if (poCameraActor->GetName().Contains(TEXT("CameraActor")))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, poCameraActor->GetName());
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(poCameraActor->GetName()));
			poCameraActor->Destroy();
			break;
		}
	}

	// only spawn camera in client/listenserver mode
	if (GetNetMode() != NM_DedicatedServer)
	{
		//CameraPawn = GetWorld()->SpawnActor<ACameraPawn>(ACameraPawn::StaticClass(), GetPawn()->GetActorTransform());
		CameraPawn = GetWorld()->SpawnActor<ACameraPawn>(ACameraPawn::StaticClass());
		//FTransform Transform;
		//Transform.SetRotation(FQuat::MakeFromEuler({0.000042, -50.597729, 0.595521}));
		//Transform.SetLocation({ -1379.584351, 7.022931, 947.442017 });
		//CameraPawn = GetWorld()->SpawnActor<ACameraPawn>(ACameraPawn::StaticClass(), Transform);
		SetViewTarget(CameraPawn);
		/*if (GetNetMode() == NM_Client)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  AMobaPlayerController BeginPlay NM_Client");
			UE_LOG(LogTemp, Warning, TEXT("1  AMobaPlayerController BeginPlay NM_Client"));
		}
		if (GetNetMode() == NM_DedicatedServer)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1  AMobaPlayerController BeginPlay NM_DedicatedServer");
			UE_LOG(LogTemp, Warning, TEXT("1  AMobaPlayerController BeginPlay NM_DedicatedServer"));
		}
		if (GetNetMode() == NM_Standalone)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 AMobaPlayerController BeginPlay NM_Standalone");
			UE_LOG(LogTemp, Warning, TEXT("1 AMobaPlayerController BeginPlay NM_Standalone"));
		}
		if (GetNetMode() == NM_ListenServer)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1 AMobaPlayerController BeginPlay NM_ListenServer");
			UE_LOG(LogTemp, Warning, TEXT("1 AMobaPlayerController BeginPlay NM_ListenServer"));
		}
		if (GetLocalRole() == ROLE_AutonomousProxy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2  AMobaPlayerControllerBeginPlay ROLE_AutonomousProxy");
			UE_LOG(LogTemp, Warning, TEXT("2  AMobaPlayerController BeginPlay ROLE_AutonomousProxy"));
		}
		if (GetLocalRole() == ROLE_Authority)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 AMobaPlayerController BeginPlay ROLE_Authority");
			UE_LOG(LogTemp, Warning, TEXT("2 AMobaPlayerController BeginPlay ROLE_Authority"));
		}
		if (GetLocalRole() == ROLE_SimulatedProxy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2 AMobaPlayerController BeginPlay ROLE_SimulatedProxy");
			UE_LOG(LogTemp, Warning, TEXT("2 AMobaPlayerController BeginPlay ROLE_SimulatedProxy"));
		}*/
	}
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
	APawn* const MyPawn = GetPawn();
	float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());
	// We need to issue move command only if far enough in order for walk animation to play correctly
	if ((Distance > 120.0f))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "SetNewMoveDestination");
	}
}

void AMobaPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "OnSetDestinationPressed");
}

void AMobaPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AMobaPlayerController::InitCamera(const FVector& t)
{
	if (CameraPawn)
	{
		CameraPawn->SetActorLocation(t);
		bCameraInited = true;
	}
}
