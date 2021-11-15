// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_EP.h"

UMainMenu_EP::UMainMenu_EP()
{

	rolTypeSelectedText = "Escoge rol";

	numPlayersText = "Num Jugadores: 0";

	numPlayersValue = 0;
}

void UMainMenu_EP::OnClickPilotButton()
{

	signalOnClickPilotButton.Broadcast();
}

void UMainMenu_EP::OnClickArtilleryButton()
{
	signalOnClickArtilleryButton.Broadcast();
}

void UMainMenu_EP::OnClickImReady()
{

	signalOnClickImReady.Broadcast();
}

void UMainMenu_EP::SetSelectionRolToPilot()
{

	rolTypeSelectedText = "Has seleccionado Piloto";
}

void UMainMenu_EP::SetSelectionRolToArtillery()
{

	rolTypeSelectedText = "Has seleccionado Artillero";
}

void UMainMenu_EP::UpdateNumPlayers()
{
	
	numPlayersText = FString::Printf(TEXT("Num Jugadores: %d"), numPlayersValue);
}

void UMainMenu_EP::SetNumPlayersValue(int32 numPlayer)
{

	numPlayersValue = numPlayer;
}


