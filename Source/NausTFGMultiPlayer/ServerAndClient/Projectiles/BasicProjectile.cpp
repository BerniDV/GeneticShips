// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/EnemyActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/Singletons/CustomGameInstance.h"

// Sets default values
ABasicProjectile::ABasicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	projectileSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComponent"));
	projectileSphereComponent->InitSphereRadius(37.5f);
	projectileSphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = projectileSphereComponent;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	projectileMesh->SetupAttachment(RootComponent);

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	projectileMovementComponent->SetUpdatedComponent(projectileSphereComponent);
	projectileMovementComponent->InitialSpeed = 3000.0f;
	projectileMovementComponent->MaxSpeed = 3000.0f;
	projectileMovementComponent->bRotationFollowsVelocity = true;
	projectileMovementComponent->ProjectileGravityScale = 0.0f;

	damage = 10.f;
	damageType = UDamageType::StaticClass();
	
}

// Called when the game starts or when spawned
void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();

	//Aplicamos tiempo maximo de vida de 10 segundos
	SetLifeSpan(10.f);

	if (HasAuthority())
	{
		
		projectileSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasicProjectile::OnProjectileImpact);
	}
	
}

void ABasicProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//projectileSphereComponent->OnComponentBeginOverlap.RemoveAll(this);
}

void ABasicProjectile::Destroyed()
{
	Super::Destroyed();

}

// Called every frame
void ABasicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicProjectile::OnProjectileImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	AActionPawn* myPawn = Cast<AActionPawn>(GetInstigator());
	AActionPawn* otherPawn = Cast<AActionPawn>(OtherActor);


	//En caso de ser del mismo equipo no hacemos nada
	if(myPawn != nullptr && otherPawn != nullptr && myPawn->GetPawnTeamId().IsSet() && otherPawn->GetPawnTeamId().IsSet() && myPawn->GetPawnTeamId().GetValue() == otherPawn->GetPawnTeamId().GetValue())
	{

		return;
	}

	//Si colisionan dos proyectiles no hacemos nada
	if(Cast<ABasicProjectile>(OtherActor) || (Cast<AEnemyActionPawn>(OtherActor) && Cast<AEnemyActionPawn>(GetOwner())))
	{

		return;
	}

	//Si no colisiona con nuestro propio actor aplicamos daño
	if (OtherActor && GetOwner() && GetOwner()->GetInstigatorController() != nullptr && OtherActor && OtherActor->GetInstigatorController() != GetOwner()->GetInstigatorController())
	{
		//Aplicamos particulas de contacto y lo destruimos
		SpawnParticles();
		UGameplayStatics::ApplyDamage(OtherActor, damage, GetOwner()->GetInstigatorController(), this, damageType);
		
	}

	Destroy();
}

bool ABasicProjectile::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget,
	const FVector& SrcLocation) const
{
	//Hacemos que el actor sea relevante para otros actores en base a su propia posicion
	return Super::IsNetRelevantFor(RealViewer, this, SrcLocation);
}

void ABasicProjectile::SpawnParticles_Implementation()
{

	if(!HasAuthority())
	{

		AActionPlayerController* PC = Cast<AActionPlayerController>(Cast<UCustomGameInstance>(GetGameInstance())->GetLocalPlayerController());

		if(PC)
			PC->SpawnParticlesAtLocation(GetActorLocation(), FVector(1));
		
	}
	
}

