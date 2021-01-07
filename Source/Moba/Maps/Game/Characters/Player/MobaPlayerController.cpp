// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobaPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MobaCharacter.h"
#include "Engine/World.h"
#include "CameraPawn.h"

AMobaPlayerController::AMobaPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AMobaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CameraPawn = GetWorld()->SpawnActor<ACameraPawn>(ACameraPawn::StaticClass(), GetPawn()->GetActorTransform());
	SetViewTarget(CameraPawn);
}

void AMobaPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FHitResult Hit;
	//GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	//CameraPawn->GetCursorToWorld()->SetWorldLocation(Hit.Location);
	//CameraPawn->GetCursorToWorld()->SetWorldRotation(Hit.ImpactNormal.Rotation());
	//if (bMoveToMouseCursor)
	//{
	//	MoveToMouseCursor(Hit);
	//}
}

void AMobaPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//CameraPawn->SetActorLocation(GetPawn()->GetActorTransform().GetLocation());
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	CameraPawn->GetCursorToWorld()->SetWorldLocation(Hit.Location);
	CameraPawn->GetCursorToWorld()->SetWorldRotation(Hit.ImpactNormal.Rotation());
	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor(Hit);
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
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AMobaPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMobaPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
