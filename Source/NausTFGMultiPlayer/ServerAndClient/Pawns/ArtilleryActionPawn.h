// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPawn.h"
#include "ArtilleryActionPawn.generated.h"


class USoundCue;
class URotationComponent;
class ABasicProjectile;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AArtilleryActionPawn : public AActionPawn
{
	GENERATED_BODY()

public:

	AArtilleryActionPawn();

	virtual void Fire() override;
	virtual void StopFire() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Fire(FVector locationToFire);

	UFUNCTION(NetMulticast, Reliable)
	void ClientFireSound();

	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

	virtual void ExecuteRotation(FRotator rotator) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	virtual void PlayDeath_Implementation() override;

	virtual void PostInitializeComponents() override;

protected:

	virtual void Tick(float DeltaSeconds) override;

protected:

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<ABasicProjectile> projectile;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Replicated)
	URotationComponent* rotationComponent;

	//sound (se hara en una clase propia como el visual controller para las particulas en el controlador de presentacion)
	UPROPERTY()
	USoundCue* gunAudioCue;

	UPROPERTY()
	UAudioComponent* gunAudioComponent;

private:

	UPROPERTY(Replicated)
	FVector position;
};
