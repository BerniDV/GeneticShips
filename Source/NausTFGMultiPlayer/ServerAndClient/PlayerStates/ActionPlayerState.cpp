// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerState.h"

#include "NausTFGMultiPlayer/ServerAndClient/GameStates/ActionGameState.h"
#include "Net/UnrealNetwork.h"

AActionPlayerState::AActionPlayerState()
{

	
	health = maxHealth;
}

void AActionPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AActionPlayerState, health);
	DOREPLIFETIME(AActionPlayerState, teamID);
}

float AActionPlayerState::GetHealth()
{

	return health;
}

void AActionPlayerState::SetHealth(float value)
{

	health = value;

	OnHealthUpdate();
}

void AActionPlayerState::AddHealth(float value)
{

	if (health + value <= maxHealth)
		health += value;

	OnHealthUpdate();
}

void AActionPlayerState::SetTeamID(int value)
{

	teamID = value;
}

int AActionPlayerState::GetTeamID()
{

	return teamID;
}

void AActionPlayerState::OnHealthUpdate()
{

	//lo que quiero que pase en todos los clientes cuando la vida se modifique
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Tu vida es: %f"), health));

	if(health <=0.f)
		Cast<AActionGameState>(GetWorld()->GetGameState())->PlayerDead();
}
