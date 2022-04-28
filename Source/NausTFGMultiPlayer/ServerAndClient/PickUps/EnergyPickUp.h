// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickUp.h"
#include "EnergyPickUp.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AEnergyPickUp : public ABasePickUp
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickedUp);
	FPickedUp signalPickedUp;

	AEnergyPickUp();

protected:

	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	virtual void Tick(float DeltaSeconds) override;


public:

	UFUNCTION()
	void OverlapDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(NetMulticast, Reliable)
	void Client_SetActorLocation(FVector newLocation);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* meshComponent;

private:

	float EnergyAmount;

	
	
};

