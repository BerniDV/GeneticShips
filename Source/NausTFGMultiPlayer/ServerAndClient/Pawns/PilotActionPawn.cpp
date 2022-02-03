// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionPawn.h"

#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/RotationComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/TranslationComponent.h"
#include "Net/UnrealNetwork.h"

APilotActionPawn::APilotActionPawn()
{

	bReplicates = true;
	
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pilot Pawn Prepared"));


	translationComponent = CreateDefaultSubobject<UTranslationComponent>(TEXT("translationComponent"));
	translationComponent->SetIsReplicated(true);

	rotationComponent = CreateDefaultSubobject<URotationComponent>(TEXT("rotationComponent"));
	rotationComponent->SetIsReplicated(true);

	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComponent"));
	SetRootComponent(collisionBox);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	meshComponent->SetupAttachment(RootComponent);

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(RootComponent);
	springArm->TargetArmLength = 300.f;
	springArm->bUsePawnControlRotation = false;
	springArm->bInheritPitch = false;
	springArm->bInheritRoll = false;
	springArm->bInheritYaw = false;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false; 
	//NetUpdateFrequency = 2.5f;
	
}

void APilotActionPawn::BeginPlay()
{
	Super::BeginPlay();

	//estos valores pueden variar para personalizar la nave
	speedDropRate = 300.f;
	defaultMaxAcceleration = 400;
	maxAcceleration = 400;
	defaultMaxSpeed = 1000;
	maxSpeed = 1000;
	accelerationSpeed = 50.f;
	decelerationSpeed = 100.f;
	maneuverabilityInPercent = 100.f;

	translationComponent->Inicialite(speedDropRate, defaultMaxAcceleration, defaultMaxSpeed, maxAcceleration, maxSpeed, accelerationSpeed, decelerationSpeed, maneuverabilityInPercent);
}

void APilotActionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void APilotActionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	
}

void APilotActionPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APilotActionPawn, translationComponent);
	DOREPLIFETIME(APilotActionPawn, rotationComponent);
	
}

void APilotActionPawn::MoveForward(float movement)
{

	translationComponent->MoveForward(movement);
}

void APilotActionPawn::MoveRight(float movement)
{

	translationComponent->MoveRight(movement);
}

void APilotActionPawn::ExecuteRotation(FRotator rotator)
{
	
	rotationComponent->ExecuteRotation(rotator);
}

void APilotActionPawn::ImpulseON()
{

	//float maxSpeed = translationComponent->GetMaxSpeed();

	translationComponent->SetMaxSpeed(maxSpeed * 7);
	translationComponent->SetCurrentSpeed(maxSpeed * 3);

	//float maxAcceleration = translationComponent->GetMaxAcceleration();

	translationComponent->SetMaxAcceleration(maxAcceleration * 5);
	translationComponent->SetCurrentAcceleration(maxAcceleration * 4);
	
}

void APilotActionPawn::ImpulseOff()
{

	translationComponent->ResetSpeedAndAcceleration();
}

void APilotActionPawn::DecelerationON()
{


	translationComponent->SetMaxSpeed(maxSpeed/4);


	translationComponent->SetMaxAcceleration(maxAcceleration/4);

}

void APilotActionPawn::DecelerationOff()
{

	translationComponent->ResetSpeedAndAcceleration();
}

void APilotActionPawn::BoostSpeed(float Value)
{

	translationComponent->BoostSpeed(Value);
}

USpringArmComponent* APilotActionPawn::GetSpringArmComponent()
{

	return springArm;
}
