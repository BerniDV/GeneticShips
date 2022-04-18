// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerDefaultBehaviour.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "ActionPlayerController.generated.h"

class AActionPawn;
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

	UFUNCTION(Server, WithValidation, Reliable)
	void SetPlayerHealth(float value);

	UFUNCTION(Server, WithValidation, Reliable)
	void ApplyDamage(float DamageAmount, FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser);


	int GetTeamId();

	float GetCadency();
	float GetTimeSinceLastProjectile();

	AActionPlayerControllerImpl* GetPlayerControllerImpl();

	void SetInputEnabled(bool enable);

	void SpawnParticlesAtLocation(FVector Location, FVector Scale);
	void SpawnFollowingParticles(USceneComponent* AttatchTo, FVector Scale);

	UFUNCTION(Client, Reliable)
	void UpdateRound();

	UFUNCTION(Client, Reliable)
	void UpdateEnemies();

	virtual void InitializePresentationController() override;

	
	//Comandos para la consola

	UFUNCTION(Exec)
		void SetNewRound(int round);

	UFUNCTION(Server, WithValidation, Reliable)
		void SetRoundServer(int round);

	UFUNCTION(Exec)
		void SetNumEnemies(int enemies);

	UFUNCTION(Server, WithValidation, Reliable)
		void SetNumEnemiesServer(int enemies);

	UFUNCTION()
	void UpdateClientHealth();

	float GetPlayerMaxHealth();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;


private:

	UPROPERTY(ReplicatedUsing = Client_InitializeClientPlayerControllerImpl)
	AActionPlayerControllerImpl* playerControllerImpl;

	NausTFGRolTypes playerRole;

	UClass* pilotReference;
	UClass* artilleryReference;

	UPROPERTY(ReplicatedUsing = UpdateClientHealth)
	float playerHealth;

	float maxPlayerHealth;

	
};
