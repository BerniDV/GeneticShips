// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActionPawn.h"

#include "PilotActionPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Chromosome.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Controllers/AIBaseController.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/Singletons/CustomGameInstance.h"
#include "Net/UnrealNetwork.h"

AEnemyActionPawn::AEnemyActionPawn()
{
	
	bReplicates = true;

	SetReplicateMovement(false);

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComponent"));
	RootComponent = boxComponent;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	meshComponent->SetupAttachment(RootComponent);

	enemyChromosome = nullptr;

	id = -1;
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

	DOREPLIFETIME(AEnemyActionPawn, enemyChromosome);
	DOREPLIFETIME(AEnemyActionPawn, id);
	DOREPLIFETIME(AEnemyActionPawn, position);
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

	position = newPosition;
}

void AEnemyActionPawn::EnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//UE_LOG(LogTemp, Warning, TEXT("Enemy Overlap"));
	UGameplayStatics::ApplyDamage(OtherActor, 20.f, nullptr, this, damageType);
}


void AEnemyActionPawn::BeginPlay()
{
	Super::BeginPlay();
		
	position = GetActorLocation();

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

	FMath::VInterpConstantTo(GetActorLocation(), position, DeltaSeconds, (GetActorLocation()-position).Size()/DeltaSeconds);
	SetActorLocation(position);
		
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

