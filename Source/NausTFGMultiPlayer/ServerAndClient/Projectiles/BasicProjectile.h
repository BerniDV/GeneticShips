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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
