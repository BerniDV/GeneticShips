// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameState.h"

#include "GameFramework/PlayerState.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "Net/UnrealNetwork.h"

AActionGameState::AActionGameState()
{

	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	round = 0;
	timeUntilNextEvent = 0;
	enemiesAlive = 0;
	countSeconds = 0.f;
}

void AActionGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AActionGameState, round);
	DOREPLIFETIME(AActionGameState, enemiesAlive);
	DOREPLIFETIME(AActionGameState, timeUntilNextEvent);
}

void AActionGameState::PlayerDead()
{

	signalPlayerDead.Broadcast();
}

void AActionGameState::SetRound(int newRound)
{
	round = newRound;
	ClientUpdateRound();

}

void AActionGameState::ClientUpdateRound_Implementation()
{

	signalNewRound.Broadcast();
}


void AActionGameState::ClientUpdateEnemies_Implementation()
{

	signalEnemiesAlive.Broadcast();
}

void AActionGameState::ClientUpdateTimeUntilNextEvent_Implementation()
{

	signalTimer.Broadcast();
}

int AActionGameState::GetRound()
{

	return round;
}

int AActionGameState::GetEnemiesAlive()
{

	return enemiesAlive;
}

void AActionGameState::SetEnemiesAlive(int numEnemies)
{

	enemiesAlive = numEnemies;
	ClientUpdateEnemies();
}

void AActionGameState::SetTimeUntilNextEvent(int timeInSeconds)
{
	if(HasAuthority())
	{
		timeUntilNextEvent = timeInSeconds;
		ClientUpdateTimeUntilNextEvent();
	}
		
}

int AActionGameState::GetTimeUntilNextEvent()
{

	return timeUntilNextEvent;
}

void AActionGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(HasAuthority() && timeUntilNextEvent > 0.f)
	{

		countSeconds += DeltaSeconds;

		if(countSeconds > 1)
		{

			countSeconds = 0.f;
			timeUntilNextEvent--;

			if(timeUntilNextEvent >= 0)
				SetTimeUntilNextEvent(timeUntilNextEvent);
		}
		
	}
}


