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
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/RotationComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/TranslationComponent.h"
#include "Net/UnrealNetwork.h"

AEnemyActionPawn::AEnemyActionPawn()
{
	
	bReplicates = true;

	SetReplicateMovement(false);
	
	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComponent"));
	
	RootComponent = boxComponent;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	meshComponent->SetupAttachment(RootComponent);

	translationComponent = CreateDefaultSubobject<UTranslationComponent>(TEXT("movementComponent"));
	translationComponent->SetIsReplicated(true);

	rotationComponent = CreateDefaultSubobject<URotationComponent>(TEXT("rotationComponent"));
	rotationComponent->SetIsReplicated(true);

	enemyChromosome = nullptr;

	id = -1;

	ConstructorHelpers::FClassFinder <ABasicProjectile> refBasicProjectileBP(TEXT("/Game/ServerAndClient/Projectiles/BasicProjectile_BP"));
	projectile = refBasicProjectileBP.Class;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
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
	DOREPLIFETIME(AEnemyActionPawn, id);
	//DOREPLIFETIME(AEnemyActionPawn, position);
}

void AEnemyActionPawn::InitMovementCompnent(float _speedDropRate, float _defaultMaxAcceleration, float _defaultMaxSpeed,
	float _maxAcceleration, float _maxSpeed, float _accelerationSpeed, float _decelerationSpeed,
	float _meneuverabilityInPercent)
{

	translationComponent->Inicialite(_speedDropRate, _defaultMaxAcceleration, _defaultMaxSpeed, _maxAcceleration, _maxSpeed, _accelerationSpeed, _decelerationSpeed, _meneuverabilityInPercent);
}

void AEnemyActionPawn::SetRandomGenes()
{

	enemyChromosome->SetRandomGenes();
}

void AEnemyActionPawn::ApplyFenotipe()
{

	enemyChromosome->ApplyFenotipe();
}

void AEnemyActionPawn::ApplyMovementGenes()
{

	enemyChromosome->ApplyMovementGenes();
}

void AEnemyActionPawn::ApplyHealthGenes()
{
	
	enemyChromosome->ApplyHealthGenes();
}

void AEnemyActionPawn::SetChromosome(AChromosome* newChromosome)
{

	enemyChromosome = newChromosome;

	ApplyFenotipe();
	ApplyMovementGenes();
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
	OnEnemyDead();
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
	{

		float impactDamage = GetChromosome()->GetGene(Gene::impactDamage);
		UGameplayStatics::ApplyDamage(OtherActor, impactDamage, nullptr, this, damageType);

		enemyChromosome->AddToGene(Gene::damageCaused, impactDamage);

	}
		
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
	//SetActorRotation(rotator);
}

FVector AEnemyActionPawn::GetPredictedPosition()
{

	return translationComponent->GetPredictedPosition();
}

float AEnemyActionPawn::GetInterpolationSpeed()
{

	return translationComponent->GetInterpolationSpeed();
}

void AEnemyActionPawn::OnEnemyDead()
{

	signalOnEnemyDead.Broadcast();
}

void AEnemyActionPawn::SetEmissiveColor(FLinearColor color)
{

	emissiveMaterial->SetVectorParameterValue(TEXT("EmissiveColor"), color);
}

void AEnemyActionPawn::SetColorAllClients_Implementation(FLinearColor color)
{

	emissiveMaterial->SetVectorParameterValue(TEXT("EmissiveColor"), color);
}

void AEnemyActionPawn::Server_Fire_Implementation(FVector locationToFire, FVector target)
{

	const FVector spawnLocation = locationToFire;
	const FRotator spawnRotation = (target - spawnLocation).Rotation();

	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;
	
	ABasicProjectile* BasicProjectile = GetWorld()->SpawnActor<ABasicProjectile>(projectile, spawnLocation, spawnRotation, spawnParameters);
	BasicProjectile->SetDamage(GetChromosome()->GetGene(Gene::bulletDamage));

}

bool AEnemyActionPawn::Server_Fire_Validate(FVector locationToFire, FVector target)
{

	return true;
}


void AEnemyActionPawn::BeginPlay()
{
	Super::BeginPlay();
		
	//position = GetActorLocation();

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	auto material = meshComponent->GetMaterial(2);

	emissiveMaterial = UMaterialInstanceDynamic::Create(material, this);

	meshComponent->SetMaterial(2, emissiveMaterial);

	//FLinearColor color(FMath::FRandRange(0, 1), FMath::FRandRange(0, 1), FMath::FRandRange(0, 1));

	//emissiveMaterial->SetVectorParameterValue(TEXT("EmissiveColor"), color);
	
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

