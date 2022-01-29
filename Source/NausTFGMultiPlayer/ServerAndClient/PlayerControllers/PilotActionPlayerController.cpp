// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionPlayerController.h"

#include "ActionPlayerController.h"
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

	if(cameraManager && cameraManager->GetViewTarget())
	{

		APilotActionCamera* camera = Cast<APilotActionCamera>(cameraManager->GetViewTarget());

		AActionPlayerController* PC = Cast<AActionPlayerController>(GetOwner());

		APilotActionPawn* myPawn = Cast<APilotActionPawn>(PC->GetPawn());

		float TestSensibility = 100.f;

		FRotator newRotation = myPawn->GetSpringArmComponent()->GetRelativeRotation();

		newRotation += FRotator(TestSensibility * DeltaSeconds * cameraInput.Y, TestSensibility * DeltaSeconds * cameraInput.X, 0.f);

		newRotation.Pitch = FMath::Clamp(newRotation.Pitch, -80.f, 80.f);

		myPawn->GetSpringArmComponent()->SetRelativeRotation(newRotation);

		//Esto igual deberia estar en su propia copmponente de rotacion, no obstante no veo mal que el controlador del pawn le diga como rotar
		FRotator newPawnRotation = myPawn->GetActorRotation();
		newPawnRotation += FRotator(TestSensibility * DeltaSeconds * cameraInput.Y , TestSensibility * DeltaSeconds * cameraInput.X , 0.f);
		newPawnRotation.Pitch = FMath::Clamp(newRotation.Pitch, -80.f, 80.f);

		FRotator lookAtCameraDirectionVector = camera->GetActorForwardVector().Rotation();

		FRotator newPawnRotator = FMath::RInterpConstantTo(myPawn->GetActorRotation(), lookAtCameraDirectionVector, DeltaSeconds, 90.f);

		myPawn->SetActorRotation(newPawnRotator);

		//Justo abajo esta comentada la manera de dar mas dinamismo a la camara en caso que consiga desvincularla del pawn y hacer que orbite y lo siga de forma independiente
		/*
		  FVector directionLookAt = PC->GetPawn()->GetActorLocation() - camera->GetActorLocation();
		  FRotator cameraRotation = directionLookAt.Rotation();

		  FRotator newCameraRotator = FMath::RInterpConstantTo(camera->GetActorRotation(), cameraRotation, DeltaSeconds, 70.f);

		  camera->SetActorRotation(newCameraRotator);
		*/

		GEngine->AddOnScreenDebugMessage(-1, -5, FColor::Red, myPawn->GetActorForwardVector().ToString());
		GEngine->AddOnScreenDebugMessage(-1, -5, FColor::Blue, newPawnRotation.ToString());
		GEngine->AddOnScreenDebugMessage(-1, -5, FColor::Emerald, myPawn->GetActorRotation().ToString());

	}

}

UClass* APilotActionPlayerController::GetDefaultPawn()
{

	return reference;
}

void APilotActionPlayerController::Rotate(float turnValue)
{

	AActionPlayerController* playerController = Cast<AActionPlayerController>(GetOwner());
	Cast<AActionPawn>(playerController->GetPawn())->ExecuteRotation(turnValue);
	
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
	//spawnLocation -= PC->GetPawn()->GetActorForwardVector() * 400.f;
	//spawnLocation += PC->GetPawn()->GetActorUpVector() * 150.f;

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





