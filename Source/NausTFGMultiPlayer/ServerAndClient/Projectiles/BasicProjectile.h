// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
UCLASS()
class NAUSTFGMULTIPLAYER_API ABasicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnProjectileImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

	UFUNCTION(NetMulticast, Reliable)
	void SpawnParticles();

	UFUNCTION(NetMulticast, Reliable)
	void SpawnHitSound(AActor* spawnDamaged);

	void SetDamage(float _damage);


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		class UParticleSystem* explosionEffect;

private:

	UPROPERTY(VisibleAnywhere)
	USphereComponent* projectileSphereComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* projectileMesh;

	UPROPERTY(VisibleAnywhere)
	float damage;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UDamageType> damageType;

	UProjectileMovementComponent* projectileMovementComponent;


};


