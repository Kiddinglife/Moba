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
#include "Blueprint/WidgetLayoutLibrary.h"

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
}

void AMobaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeGameAndUI);

	//// remove the default camera actor in the level as it is not used at all
	//TArray<AActor*> CameraActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);
	//for (AActor* CameraActor : CameraActors)
	//{
	//	if (CameraActor->GetName() == TEXT("TopDownCameraActor"))
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("AMobaPlayerController::BeginPlay()  camera %s"), *CameraActor->GetName()));
	//		TopDownCamera = Cast<ACameraActor>(CameraActor);
	//	}
	//}
	//InitCamera();
}

void AMobaPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMobaPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (!TopDownCamera) return;
	//CameraPawn->SetActorLocation(GetPawn()->GetActorTransform().GetLocation());
	//CameraPawn->GetCursorToWorld()->SetWorldLocation(Hit.Location);
	//CameraPawn->GetCursorToWorld()->SetWorldRotation(Hit.ImpactNormal.Rotation());
	// keep updating the destination every tick while desired
	int CursorSpeed = 2500;
	UpdateCameraView(CursorSpeed* DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%.2f"), DeltaTime));
	MoveToMouseCursor();
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
}

void AMobaPlayerController::MoveToMouseCursor()
{
	if (bMoveToMouseCursor)
	{
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit) SetNewMoveDestination(Hit.ImpactPoint);
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

void AMobaPlayerController::InitCamera()
{
	ShowNetModeAndRole("AMobaPlayerController::InitCamera", true);
	// Only spawn camera in client/listenserver mode
	if (GetNetMode() == NM_Client)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("GetNetMode() == NM_Client")));
		// remove the default camera actor in the level as it is not used at all
		TArray<AActor*> CameraActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);
		for (AActor* CameraActor : CameraActors)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("AMobaPlayerController::BeginPlay()  camera %s"), *CameraActor->GetName()));
			if (CameraActor->GetName().Contains(TEXT("CameraActor")))
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("AMobaPlayerController::BeginPlay() Removed camera %s"), *CameraActor->GetName()));
				UE_LOG(LogTemp, Warning, TEXT(" AMobaPlayerController::InitCamera() Removed default camera %s"), *(CameraActor->GetName()));
				check(CameraActor->Destroy());
			}
		}

		TArray<AActor*> PlayerStartActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActor);
		check(PlayerStartActor.Num() == 1);
		//CameraPawn = GetWorld()->SpawnActor<ACameraPawn>(ACameraPawn::StaticClass(), GetPawn()->GetActorTransform());
		//CameraPawn = GetWorld()->SpawnActor<ACameraPawn>(ACameraPawn::StaticClass());
		CameraPawn = GetWorld()->SpawnActorDeferred<ACameraPawn>(ACameraPawn::StaticClass(), FTransform::Identity, this);
		CameraPawn->SetReplicates(false);
		CameraPawn->bNetLoadOnClient = false;
		CameraPawn->SetReplicatingMovement(false);
		CameraPawn->bAlwaysRelevant = false;
		CameraPawn->FinishSpawning(FTransform::Identity, true);
		CameraPawn->SetActorLocation(PlayerStartActor[0]->GetActorLocation());
		SetViewTarget(CameraPawn);
		UE_LOG(LogTemp, Warning, TEXT(" AMobaPlayerController::InitCamera() Spawn camera %s"), *(CameraPawn->GetName()));
	}
}

void AMobaPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//ShowNetModeAndRole("AMobaPlayerController::OnPossess");
	//UE_LOG(LogTemp, Warning, TEXT("InPawn name: %s"), *(InPawn->GetName()));
}

void AMobaPlayerController::UpdateCameraView(float CameraOffset)
{
	float  MousePositionX, MousePositionY;
	// WHEN HIT LEFT EGE QUICKLY I SAW X 0.0 Y 0.0 SOMETIMES RETURN FALSE
	//if(!GetMousePosition(MousePositionX, MousePositionY)) return;
	int ViewporX, ViewporY;
	GetViewportSize(ViewporX, ViewporY);
	
	// editor will always use the newest x y. 
	// But we cannot use this becsue it will not update when it is in real game. 
	//auto ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
	//ViewporX = ViewportSize.X;
	//ViewporY = ViewportSize.Y;
	auto MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	// must need abs otherwise when play in editor the two viewports will have nagative mousepostion
    // that cause a wired situation where you move in one viewport will make it move in the other viewport
	MousePositionX = FMath::Abs(MousePosition.X);
	MousePositionY = FMath::Abs(MousePosition.Y);
	check(GetWorld());
	check(GetWorld()->GetGameViewport());
	float ViewPortScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld()->GetGameViewport());
	MousePositionX *= ViewPortScale;
	MousePositionY *= ViewPortScale;

	FVector OffSet = FVector::ZeroVector;
	//UE_LOG(LogTemp, Warning, TEXT("MousePositionX %.2f, MousePositionY %.2f"), MousePositionX, MousePositionY);
	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT(" %.2f | %.2f | %.2f | %.2f | %.2f"), ViewPortScale, (float)ViewporX, MousePositionX, (float)ViewporY, MousePositionY));
	if (MousePositionX < 0.0f || MousePositionX > ViewporX || MousePositionY < 0.0f || MousePositionY > ViewporY) return;
	if(FMath::IsNearlyEqual(MousePositionX, 0.f, 15.f))
	{
		OffSet.Y = -CameraOffset; 			// left 
		if (FMath::IsNearlyEqual(MousePositionY, 0.f, 15.f))
		{
			OffSet.X = CameraOffset; // left up
			//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("left up %.2f | %.2f | %.2f | %.2f"), (float)ViewporX, MousePositionX, (float)ViewporY, MousePositionY));
		} 
		else if (FMath::IsNearlyEqual(MousePositionY, (float)ViewporY, 15.f))
		{
			OffSet.X = -CameraOffset; // left bot 
			//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("left bot  %.2f | %.2f | %.2f | %.2f"), (float)ViewporX, MousePositionX, (float)ViewporY, MousePositionY));
		}
	}
	else if (FMath::IsNearlyEqual(MousePositionY, 0.f, 15.f))
	{
		OffSet.X = CameraOffset; // up 
		if (FMath::IsNearlyEqual(MousePositionX, (float)ViewporX, 100.f))
		{
			OffSet.Y = CameraOffset;  // right up
			//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("up right %.2f | %.2f | %.2f | %.2f"), (float)ViewporX, MousePositionX, (float)ViewporY, MousePositionY));
		} else if (FMath::IsNearlyEqual(MousePositionX, 0.f, 15.f))
		{
			OffSet.Y = -CameraOffset; // left up
			//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT(" up left %.2f | %.2f | %.2f | %.2f"), (float)ViewporX, MousePositionX, (float)ViewporY, MousePositionY));
		}
	}
	else if (FMath::IsNearlyEqual(MousePositionX, (float)ViewporX, 15.f))
	{
		OffSet.Y = CameraOffset;  // right 
		if (FMath::IsNearlyEqual(MousePositionY, (float)ViewporY, 15.f))
		{
			OffSet.X = -CameraOffset;  // right bot
			//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("right bot %.2f | %.2f | %.2f | %.2f"), (float)ViewporX, MousePositionX, (float)ViewporY, MousePositionY));
		}
		else if (FMath::IsNearlyEqual(MousePositionY, 0.f, 15.f))
		{
			OffSet.X = CameraOffset; // right up 
			//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("right up %.2f | %.2f | %.2f | %.2f"), (float)ViewporX, MousePositionX, (float)ViewporY, MousePositionY));
		}
	}
	else if (FMath::IsNearlyEqual(MousePositionY, (float)ViewporY, 15.f))
	{
		OffSet.X = -CameraOffset; // bot 
		if (FMath::IsNearlyEqual(MousePositionX, (float)ViewporX, 15.f))
		{
			OffSet.Y = CameraOffset;  // right bot
			//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("bot right %.2f | %.2f | %.2f | %.2f"), (float)ViewporX, MousePositionX, (float)ViewporY, MousePositionY));
		}
		else if (FMath::IsNearlyEqual(MousePositionX, 0.f, 15.f))
		{
			OffSet.Y = -CameraOffset; // left bot
			//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("bot left %.2f | %.2f | %.2f | %.2f"), (float)ViewporX, MousePositionX, (float)ViewporY, MousePositionY));
		}
	}
	TopDownCamera->AddActorWorldOffset(OffSet);
}

void AMobaPlayerController::ShowNetModeAndRole(const FString& str, bool bOnScreenMsg)
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
