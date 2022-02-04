// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABasicProjectile::ABasicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	projectileSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComponent"));
	projectileSphereComponent->InitSphereRadius(37.5f);
	projectileSphereComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = projectileSphereComponent;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	projectileMesh->SetupAttachment(RootComponent);

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	projectileMovementComponent->SetUpdatedComponent(projectileSphereComponent);
	projectileMovementComponent->InitialSpeed = 1500.0f;
	projectileMovementComponent->MaxSpeed = 1500.0f;
	projectileMovementComponent->bRotationFollowsVelocity = true;
	projectileMovementComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

