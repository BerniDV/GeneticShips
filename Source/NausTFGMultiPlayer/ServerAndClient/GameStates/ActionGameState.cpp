// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameState.h"

#include "Net/UnrealNetwork.h"

AActionGameState::AActionGameState()
{

	PrimaryActorTick.bCanEverTick = false;
}

void AActionGameState::PlayerDead()
{

	signalPlayerDead.Broadcast();
}


