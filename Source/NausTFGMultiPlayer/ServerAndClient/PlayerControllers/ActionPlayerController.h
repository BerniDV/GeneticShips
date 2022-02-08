// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerDefaultBehaviour.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "ActionPlayerController.generated.h"

struct MatchOptions;
class AActionPlayerControllerImpl;
class UReferencePawnsFactory;
class AArtilleryActionPawn;
class APilotActionPawn;
enum class NausTFGRolTypes : uint8;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AActionPlayerController : public APlayerControllerDefaultBehaviour
{
	GENERATED_BODY()

public:

	AActionPlayerController();

	 virtual void BindSignals() override;

	UClass* GetDefaultPawn();

	void Initialize(MatchOptions matchOptions);

	virtual void SetupInputComponent() override;

	UFUNCTION(Client, Reliable)
	void Client_InitializeClientPlayerControllerImpl();

	void SpawnActionCamera();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	float GetPlayerHealth();

	void SetPlayerHealth(float value);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	int GetTeamId();

	float GetCadency();
	float GetTimeSinceLastProjectile();

	AActionPlayerControllerImpl* GetPlayerControllerImpl();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;


private:

	UPROPERTY(ReplicatedUsing = Client_InitializeClientPlayerControllerImpl)
	AActionPlayerControllerImpl* playerControllerImpl;
	
};
