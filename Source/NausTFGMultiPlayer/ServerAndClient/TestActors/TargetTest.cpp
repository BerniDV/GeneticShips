// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTest.h"

#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/Projectiles/BasicProjectile.h"
#include "NausTFGMultiPlayer/ServerAndClient/Singletons/CustomGameInstance.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATargetTest::ATargetTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	testActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	testActorMesh->SetupAttachment(RootComponent);

	Health = 100.f;
	damageType = UDamageType::StaticClass();
}

// Called when the game starts or when spawned
void ATargetTest::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
		OnActorBeginOverlap.AddDynamic(this, &ATargetTest::TargetTestOverlap);

}

void ATargetTest::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	
}

// Called every frame
void ATargetTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetTest::Destroyed()
{
	
	Super::Destroyed();

}



float ATargetTest::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                              AActor* DamageCauser)
{

	float currenthealt = Health - DamageAmount;

	Health = currenthealt;

	if (Health <= 0)
	{

		SetHidden(true);
		SetActorEnableCollision(false);
		SpawnParticlesDeath();
		GetWorld()->GetTimerManager().SetTimer(timerDeath, this, &ATargetTest::DeleteActor, 3.f, false);
		//Destroy();
	}
		

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Current healt: %f"), Health));

	return currenthealt;
}

void ATargetTest::TargetTestOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

	UE_LOG(LogTemp, Warning, TEXT("Target Overlap"));
	UGameplayStatics::ApplyDamage(OtherActor, 50.f, nullptr, this, damageType);
}

void ATargetTest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATargetTest, Health);
}

void ATargetTest::DeleteActor()
{

	Destroy();
}

void ATargetTest::SpawnParticlesDeath_Implementation()
{

	if (!HasAuthority())
	{

		AActionPlayerController* PC = Cast<AActionPlayerController>(Cast<UCustomGameInstance>(GetGameInstance())->GetLocalPlayerController());

		if(PC)
			PC->SpawnParticlesAtLocation(GetActorLocation(), FVector(7));

	}
}

