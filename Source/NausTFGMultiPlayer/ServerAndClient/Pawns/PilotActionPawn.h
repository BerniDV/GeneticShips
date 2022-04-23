// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPawn.h"
#include "PilotActionPawn.generated.h"

class USoundCue;
class UBoxComponent;
class USpringArmComponent;
class URotationComponent;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API APilotActionPawn : public AActionPawn
{
	GENERATED_BODY()


public:

	APilotActionPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;


	virtual void MoveForward(float movement) override;

	virtual void MoveRight(float movement) override;

	virtual void ExecuteRotation(FRotator executeRotation) override;

	virtual void ImpulseON() override;

	virtual void ImpulseOff() override;

	virtual void DecelerationON() override;

	virtual void DecelerationOff() override;

	virtual void BoostSpeed(float Value) override;

	virtual bool HasPredictedMovement() override;

	UFUNCTION()
	void OnPilotOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	USpringArmComponent* GetSpringArmComponent();

	
	float GetCurrentSpeed();
	float GetMaxSpeed();
	FVector GetPredictedPosition();
	float GetInterpolationSpeed();
	FVector GetLastPosition();
	FVector GetReplicatedPosition();

	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

    virtual void PlayDeath() override;

	UFUNCTION(NetMulticast, Reliable)
	void SpawnExplosionParticlesAtActorLocation();

	UFUNCTION(NetMulticast, Reliable)
	void SpawnFollowingFireParticles();

	void InitializeMovement();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	UTranslationComponent* translationComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	URotationComponent* rotationComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USpringArmComponent* springArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UBoxComponent* collisionBox;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* meshComponent;

private:

	float movementSpeedInCm;
	float defaultMaxAcceleration;
	float defaultMaxSpeed;
	float maxAcceleration;
	float maxSpeed;
	float accelerationSpeed;
	float decelerationSpeed;
	float speedDropRate;
	float maneuverabilityInPercent;

	
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UDamageType> damageType;

};
