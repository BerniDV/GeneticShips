// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotHUD_EP.h"

UPilotHUD_EP::UPilotHUD_EP()
{

	renderedLifeInPercent = 100.f;
	renderedEnergyInPercent = 100.f;
}

void UPilotHUD_EP::SetLifeRendered(float life)
{
	renderedLifeInPercent = life;
}

void UPilotHUD_EP::SetEnergyRendered(float energy)
{

	renderedEnergyInPercent = energy;
}

float UPilotHUD_EP::GetLife()
{

	return renderedLifeInPercent / 100.f;
}

float UPilotHUD_EP::GetEnergy()
{

	return renderedEnergyInPercent / 100.f;
}
