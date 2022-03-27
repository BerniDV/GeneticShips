// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActionPawn.h"

#include "PilotActionPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Chromosome.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Controllers/AIBaseController.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/Singletons/CustomGameInstance.h"
#include "NausTFGMultiPlayer/ServerAndClient/Projectiles/BasicProjectile.h"
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/enemyMovementComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/RotationComponent.h"
#include "Net/UnrealNetwork.h"

AEnemyActionPawn::AEnemyActionPawn()
{
	
	bReplicates = true;

	SetReplicateMovement(false);

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComponent"));
	RootComponent = boxComponent;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	meshComponent->SetupAttachment(RootComponent);

	translationComponent = CreateDefaultSubobject<UenemyMovementComponent>(TEXT("translationComponent"));
	translationComponent->SetIsReplicated(true);

	rotationComponent = CreateDefaultSubobject<URotationComponent>(TEXT("rotationComponent"));
	rotationComponent->SetIsReplicated(true);

	enemyChromosome = nullptr;

	id = -1;

	ConstructorHelpers::FClassFinder <ABasicProjectile> refBasicProjectileBP(TEXT("/Game/ServerAndClient/Projectiles/BasicProjectile_BP"));
	projectile = refBasicProjectileBP.Class;
}

void AEnemyActionPawn::SetID(int32 newEnemyID)
{

	id = newEnemyID;
}

int32 AEnemyActionPawn::GetID()
{

	return id;
}


void AEnemyActionPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEnemyActionPawn, translationComponent);
	DOREPLIFETIME(AEnemyActionPawn, rotationComponent);
	DOREPLIFETIME(AEnemyActionPawn, enemyChromosome);
	DOREPLIFETIME(AEnemyActionPawn, id);
	//DOREPLIFETIME(AEnemyActionPawn, position);
}

void AEnemyActionPawn::SetRandomGenes()
{

	enemyChromosome->SetRandomGenes();
}

void AEnemyActionPawn::ApplyFenotipe()
{

	enemyChromosome->ApplyFenotipe();
}

void AEnemyActionPawn::SetChromosome(AChromosome* newChromosome)
{

	enemyChromosome = newChromosome;

	ApplyFenotipe();
}

AChromosome* AEnemyActionPawn::GetChromosome()
{

	return enemyChromosome;
}

float AEnemyActionPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float currentHealth = 100.f;

	if (AAIBaseController* IAC = Cast<AAIBaseController>(GetOwner()))
	{

		currentHealth = IAC->ApplyDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current Health: %f"), currentHealth));

	return currentHealth;
}

void AEnemyActionPawn::PlayDeath()
{

	SpawnParticlesDeath();
	SetHidden(true);
	SetActorEnableCollision(false);
	//Destroy();
}

void AEnemyActionPawn::SetPosition(FVector newPosition)
{

	//position = newPosition;
}

void AEnemyActionPawn::EnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//UE_LOG(LogTemp, Warning, TEXT("Enemy Overlap"));
	if(Cast<APilotActionPawn>(OtherActor))
		UGameplayStatics::ApplyDamage(OtherActor, 20.f, nullptr, this, damageType);
}

void AEnemyActionPawn::MoverForward(float movement)
{

	translationComponent->MoveForward(movement);
}

void AEnemyActionPawn::MoverRight(float movement)
{

	translationComponent->MoveRight(movement);
}

void AEnemyActionPawn::ExecuteRotation(FRotator rotator)
{

	rotationComponent->ExecuteRotation(rotator);
}

void AEnemyActionPawn::Server_Fire_Implementation(FVector locationToFire, FVector target)
{

	const FVector spawnLocation = locationToFire;
	const FRotator spawnRotation = (target - spawnLocation).Rotation();

	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;
	
	ABasicProjectile* BasicProjectile = GetWorld()->SpawnActor<ABasicProjectile>(projectile, spawnLocation, spawnRotation, spawnParameters);

}

bool AEnemyActionPawn::Server_Fire_Validate(FVector locationToFire, FVector target)
{

	return true;
}


void AEnemyActionPawn::BeginPlay()
{
	Super::BeginPlay();
		
	//position = GetActorLocation();

	//estos valores pueden variar para personalizar la nave, de momento tambien lo hace el cliente pero debera ser replicado y solo hacerlo el server
	float speedDropRate = 300.f;
	float defaultMaxAcceleration = 400;
	float maxAcceleration = 400;
	float defaultMaxSpeed = 1000;
	float maxSpeed = 1000;
	float accelerationSpeed = 50.f;
	float decelerationSpeed = 100.f;
	float maneuverabilityInPercent = 100.f;

	
	translationComponent->Inicialite(speedDropRate, defaultMaxAcceleration, defaultMaxSpeed, maxAcceleration, maxSpeed, accelerationSpeed, decelerationSpeed, maneuverabilityInPercent);

	if(HasAuthority())
	{

		boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActionPawn::EnemyOverlap);
	}
}

void AEnemyActionPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	
}

void AEnemyActionPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//FMath::VInterpConstantTo(GetActorLocation(), position, DeltaSeconds, (GetActorLocation()-position).Size()/DeltaSeconds);
	//SetActorLocation(position);
		
}

void AEnemyActionPawn::Destroyed()
{

	Super::Destroyed();

}

void AEnemyActionPawn::SpawnParticlesDeath_Implementation()
{
	
	if(!HasAuthority())
	{

		AActionPlayerController* PC = Cast<AActionPlayerController>(Cast<UCustomGameInstance>(GetGameInstance())->GetLocalPlayerController());

		if (PC)
			PC->SpawnParticlesAtLocation(GetActorLocation(), GetActorScale());
	}

}

