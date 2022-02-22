// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionPawn.h"

#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/RotationComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/TranslationComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/Projectiles/BasicProjectile.h"
#include "Net/UnrealNetwork.h"

APilotActionPawn::APilotActionPawn()
{

	bReplicates = true;
	
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pilot Pawn Prepared"));


	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComponent"));
	collisionBox->SetCollisionProfileName("BlockAllDynamic");
	SetRootComponent(collisionBox);

	//if (GetLocalRole() == ROLE_Authority)
	//{
		collisionBox->OnComponentHit.AddDynamic(this, &APilotActionPawn::OnPilotImpact);
		collisionBox->OnComponentBeginOverlap.AddDynamic(this, &APilotActionPawn::OnPilotOverlap);
	//}

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	meshComponent->SetupAttachment(RootComponent);

	translationComponent = CreateDefaultSubobject<UTranslationComponent>(TEXT("translationComponent"));
	translationComponent->SetIsReplicated(true);

	rotationComponent = CreateDefaultSubobject<URotationComponent>(TEXT("rotationComponent"));
	rotationComponent->SetIsReplicated(true);

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

	//NetCullDistanceSquared = 1000000.f;
	
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

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Location: " + GetActorLocation().ToString());
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

	translationComponent->SetMaxSpeed(maxSpeed * 7);
	translationComponent->SetCurrentSpeed(maxSpeed * 3);

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

bool APilotActionPawn::HasPredictedMovement()
{
	
	return true;
}

void APilotActionPawn::OnPilotImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	FVector normal = Hit.Normal;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Hit Detected");
}

void APilotActionPawn::OnPilotOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Overlap Detected");

	if(!Cast<ABasicProjectile>(OtherActor))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, destoyedParticles, GetActorLocation(), FRotator::ZeroRotator, FVector(7), true, EPSCPoolMethod::AutoRelease);
		UGameplayStatics::ApplyDamage(OtherActor, 100.f, Cast<AActionPlayerController>(GetOwner()), this, damageType);
	}
	
}

float APilotActionPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{

	float currentHealth = 100.f;

	if(AActionPlayerController* PC = Cast<AActionPlayerController>(GetOwner()))
	{

		currentHealth = PC->ApplyDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current Health: %f"), currentHealth));

	return currentHealth;
}

USpringArmComponent* APilotActionPawn::GetSpringArmComponent()
{

	return springArm;
}

float APilotActionPawn::GetCurrentSpeed()
{

	return translationComponent->GetCurrenntSpeed();
}

float APilotActionPawn::GetMaxSpeed()
{

	return translationComponent->GetMaxSpeed();
}

FVector APilotActionPawn::GetPredictedPosition()
{

	return translationComponent->GetPredictedPosition();
}

float APilotActionPawn::GetInterpolationSpeed()
{

	return translationComponent->GetInterpolationSpeed();
}

FVector APilotActionPawn::GetLastPosition()
{

	return translationComponent->GetLastPosition();
}

FVector APilotActionPawn::GetReplicatedPosition()
{

	return translationComponent->GetReplicatedPosition();
}

bool APilotActionPawn::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget,
                                        const FVector& SrcLocation) const
{
	return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
}

void APilotActionPawn::PlayDeath()
{

	UGameplayStatics::SpawnEmitterAtLocation(this, fireParticles, GetActorLocation(), FRotator::ZeroRotator, FVector(7), false, EPSCPoolMethod::AutoRelease);
	UGameplayStatics::SpawnEmitterAttached(fireParticles, collisionBox, NAME_None, FVector(ForceInit), FRotator::ZeroRotator, FVector(7), EAttachLocation::KeepRelativeOffset, true, EPSCPoolMethod::None, true);
	Cast<AActionPlayerController>(GetOwner())->SetInputEnabled(false);
}
