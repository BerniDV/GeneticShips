// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_EP.h"

void UMainMenu_EP::OnClickPilotButton()
{

	signalOnClickPilotButton.Broadcast();
}

void UMainMenu_EP::OnClickArtilleryButton()
{
	signalOnClickArtilleryButton.Broadcast();
}
