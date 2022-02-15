// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionPlayerController.h"

#include "ActionPlayerController.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "NausTFGMultiPlayer/Client/Cameras/PilotActionCamera.h"
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/RotationComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/TranslationComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"


APilotActionPlayerController::APilotActionPlayerController()
{

	bReplicates = true;
	
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pilot Controller Prepared"));

	ConstructorHelpers::FClassFinder <APilotActionPawn> refPilotActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/PilotActionPawn_BP"));
	reference = refPilotActionPawnBP.Class;

}

void APilotActionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	cameraInput = FVector2D(0.f, 0.f);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pilot Controller Prepared"));

}

void APilotActionPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(cameraManager && Cast<AActionCamera>(cameraManager->GetViewTarget()))
	{

		APilotActionCamera* camera = Cast<APilotActionCamera>(cameraManager->GetViewTarget());

		AActionPlayerController* PC = Cast<AActionPlayerController>(GetOwner());

		APilotActionPawn* myPawn = Cast<APilotActionPawn>(PC->GetPawn());

		FRotator newRotation = myPawn->GetSpringArmComponent()->GetRelativeRotation();

		newRotation += FRotator(TestSensibility * DeltaSeconds * cameraInput.Y, TestSensibility * DeltaSeconds * cameraInput.X, 0.f);

		newRotation.Pitch = FMath::Clamp(newRotation.Pitch, -80.f, 80.f);

		myPawn->GetSpringArmComponent()->SetRelativeRotation(newRotation);


		FRotator lookAtCameraDirectionVector = camera->GetActorForwardVector().Rotation();

		FRotator newPawnRotator = FMath::RInterpConstantTo(myPawn->GetActorRotation(), lookAtCameraDirectionVector, DeltaSeconds, 90.f);

		myPawn->ExecuteRotation(newPawnRotator);

	}

}


UClass* APilotActionPlayerController::GetDefaultPawn()
{

	return reference;
}

void APilotActionPlayerController::Rotate(float turnValue)
{

	AActionPlayerController* playerController = Cast<AActionPlayerController>(GetOwner());
	
}

void APilotActionPlayerController::MoveForward(float movement)
{

	AActionPlayerController* playerController = Cast<AActionPlayerController>(GetOwner());
	Cast<AActionPawn>(playerController->GetPawn())->MoveForward(movement);
}

void APilotActionPlayerController::MoveRight(float movement)
{

	AActionPlayerController* playerController = Cast<AActionPlayerController>(GetOwner());
	Cast<AActionPawn>(playerController->GetPawn())->MoveRight(movement);
}

void APilotActionPlayerController::ImpulseON()
{

	AActionPlayerController* playerController = Cast<AActionPlayerController>(GetOwner());
	Cast<AActionPawn>(playerController->GetPawn())->ImpulseON();

}

void APilotActionPlayerController::ImpulseOFF()
{
	AActionPlayerController* playerController = Cast<AActionPlayerController>(GetOwner());
	Cast<AActionPawn>(playerController->GetPawn())->ImpulseOff();
}

void APilotActionPlayerController::DecelerationON()
{
	AActionPlayerController* playerController = Cast<AActionPlayerController>(GetOwner());
	Cast<AActionPawn>(playerController->GetPawn())->DecelerationON();
}

void APilotActionPlayerController::DecelerationOff()
{

	AActionPlayerController* playerController = Cast<AActionPlayerController>(GetOwner());
	Cast<AActionPawn>(playerController->GetPawn())->DecelerationOff();

}

void APilotActionPlayerController::BoostSpeed(float value)
{

	AActionPlayerController* playerController = Cast<AActionPlayerController>(GetOwner());
	Cast<AActionPawn>(playerController->GetPawn())->BoostSpeed(value);
}

AActionCamera* APilotActionPlayerController::SpawnActionCamera()
{

	AActionPlayerController* PC = Cast<AActionPlayerController>(GetOwner());
	APilotActionPawn* pawn = Cast<APilotActionPawn>(PC->GetPawn());

	FVector spawnLocation = pawn->GetSpringArmComponent()->GetSocketLocation(USpringArmComponent::SocketName);


	FRotator spawnRotation = PC->GetPawn()->GetActorRotation();
	

	APilotActionCamera* camera = GetWorld()->SpawnActor<APilotActionCamera>(spawnLocation, spawnRotation);
	
	FVector directionLookAt = PC->GetPawn()->GetActorLocation() - camera->GetActorLocation();
	FRotator cameraRotation = directionLookAt.Rotation();


	camera->SetActorRotation(cameraRotation);

	radiusCamera = (PC->GetPawn()->GetActorLocation() - camera->GetActorLocation()).Size();


	FAttachmentTransformRules attatchRUles = FAttachmentTransformRules::KeepWorldTransform;

	camera->AttachToComponent(pawn->GetSpringArmComponent(), attatchRUles, USpringArmComponent::SocketName);

	return camera;
}

void APilotActionPlayerController::PitchCamera(float value)
{

	cameraInput.Y = value;
}

void APilotActionPlayerController::YawCamera(float value)
{

	cameraInput.X = value;
}





