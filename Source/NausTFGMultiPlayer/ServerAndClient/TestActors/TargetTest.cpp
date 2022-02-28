// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTest.h"

#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/ServerAndClient/Projectiles/BasicProjectile.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATargetTest::ATargetTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	testActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	testActorMesh->SetupAttachment(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &ATargetTest::ActorOverlaped);

	Health = 100.f;
	damageType = UDamageType::StaticClass();
}

// Called when the game starts or when spawned
void ATargetTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetTest::ActorOverlaped(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<ABasicProjectile>(OtherActor))
		UGameplayStatics::ApplyPointDamage(OtherActor, 50.f, FVector::ZeroVector, FHitResult(), nullptr, this, damageType);
}

void ATargetTest::Destroyed()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, explosionEffect, GetActorLocation(), FRotator::ZeroRotator, FVector(4), true, EPSCPoolMethod::AutoRelease);
	Super::Destroyed();

}



float ATargetTest::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                              AActor* DamageCauser)
{
	float currenthealt = Health - DamageAmount;

	Health = currenthealt;

	if (Health <= 0)
		Destroy();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Current healt: %f"), Health));

	return currenthealt;
}

void ATargetTest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATargetTest, Health);
}

