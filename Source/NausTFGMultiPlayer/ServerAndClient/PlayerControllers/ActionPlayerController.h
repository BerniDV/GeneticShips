// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerDefaultBehaviour.h"
#include "ActionPlayerController.generated.h"

class UReferencePawnsFactory;
class AArtilleryActionPawn;
class APilotActionPawn;
enum class NausTFGRolTypes_Enum : uint8;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AActionPlayerController : public APlayerControllerDefaultBehaviour
{
	GENERATED_BODY()

public:

	AActionPlayerController();

	virtual void InitializePresentationController() override;

	virtual void BindSignals() override;

	UClass* GetDefaultPawn();

	//void InitializeDefaultPawn(UReferencePawnsFactory* factoryType);
	void Initialize(NausTFGRolTypes_Enum i_type /*....*/);
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	class ActionPlayerControllerImpl;
private:

	UPROPERTY(Replicated)
	UClass* defaultPawn;

	TSubclassOf<APilotActionPawn> pilotClass;
	TSubclassOf<AArtilleryActionPawn> artilleryClass;


	

	ActionPlayerControllerImpl* m_impl;
	
};
