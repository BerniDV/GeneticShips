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

	translationComponent = CreateDefaultSubobject<UTranslationComponent>(TEXT("translationComponent"));
	translationComponent->SetIsReplicated(true);

	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComponent"));
	collisionBox->SetCollisionProfileName("BlockAllDynamic");
	SetRootComponent(collisionBox);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	meshComponent->SetupAttachment(RootComponent);

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

	

	collisionBox->OnComponentBeginOverlap.RemoveAll(this);

	if (HasAuthority())
	{

		collisionBox->OnComponentBeginOverlap.AddDynamic(this, &APilotActionPawn::OnPilotOverlap);
		//translationComponent = NewObject<UTranslationComponent>(this, FName("TranslationComp"));
	}

	

	InitializeMovement();
	
	
	
}

void APilotActionPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	
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

	translationComponent->SetMaxSpeed(maxSpeed * 3);
	translationComponent->SetCurrentSpeed(maxSpeed * 2);

	translationComponent->SetMaxAcceleration(maxAcceleration * 3);
	translationComponent->SetCurrentAcceleration(maxAcceleration * 2);
	
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


void APilotActionPawn::OnPilotOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	

	if(!Cast<ABasicProjectile>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Pilot Overlap"));
		UGameplayStatics::ApplyDamage(OtherActor, 100.f, Cast<AActionPlayerController>(GetOwner()), this, damageType);
		SpawnExplosionParticlesAtActorLocation();
	}
	
	
}

float APilotActionPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{

	float currentHealth = 100.f;

	if(AActionPlayerController* PC = Cast<AActionPlayerController>(GetOwner()))
	{

		PC->ApplyDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		//SpawnExplosionParticlesAtActorLocation();
		currentHealth = PC->GetPlayerHealth();
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current Health: %f"), currentHealth));

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

void APilotActionPawn::PlayDeath_Implementation()
{
	SpawnExplosionParticlesAtActorLocation();
	SpawnFollowingFireParticles();
	Cast<AActionPlayerController>(GetOwner())->SetInputEnabled(false);
}

void APilotActionPawn::InitializeMovement()
{

	//estos valores pueden variar para personalizar la nave x10
	speedDropRate = 3000.f / 3;
	defaultMaxAcceleration = 4000 / 3;
	maxAcceleration = 4000 / 3;
	defaultMaxSpeed = 10000;
	maxSpeed = 10000;
	accelerationSpeed = 500.f / 2;
	decelerationSpeed = 1000.f / 2;
	maneuverabilityInPercent = 15.f;

	translationComponent->Inicialite(speedDropRate, defaultMaxAcceleration, defaultMaxSpeed, maxAcceleration, maxSpeed, accelerationSpeed, decelerationSpeed, maneuverabilityInPercent);
}

void APilotActionPawn::SpawnFollowingFireParticles_Implementation()
{

	if(!HasAuthority())
	{

		AActionPlayerController* PC = Cast<AActionPlayerController>(GetOwner());

		if(PC)
			PC->SpawnFollowingParticles(collisionBox, FVector(7));

	}

}


void APilotActionPawn::SpawnExplosionParticlesAtActorLocation_Implementation()
{

	if(!HasAuthority())
	{

		AActionPlayerController* PC = Cast<AActionPlayerController>(GetOwner());

		if(PC)
			PC->SpawnParticlesAtLocation(GetActorLocation(), FVector(7));

		if (PC)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current Health: %f"), PC->GetPlayerHealth()));

	}
	
}

	
