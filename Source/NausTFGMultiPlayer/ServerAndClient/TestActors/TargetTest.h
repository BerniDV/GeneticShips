// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetTest.generated.h"

UCLASS()
class NAUSTFGMULTIPLAYER_API ATargetTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ActorOverlaped(AActor* OverlappedActor, AActor* OtherActor);

	virtual void Destroyed() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* testActorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UParticleSystem* explosionEffect;

	UPROPERTY(Replicated)
	float Health;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UDamageType> damageType;
};
