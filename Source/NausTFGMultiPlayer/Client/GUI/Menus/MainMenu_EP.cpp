// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_EP.h"

UMainMenu_EP::UMainMenu_EP()
{

	RolTypeSelectedText = "Escoge rol";
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

	RolTypeSelectedText = "Has seleccionado Piloto";
}

void UMainMenu_EP::SetSelectionRolToArtillery()
{

	RolTypeSelectedText = "Has seleccionado Artillero";
}


