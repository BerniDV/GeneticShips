// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotHUD_EP.h"

UPilotHUD_EP::UPilotHUD_EP()
{

	renderedLifeInPercent = 100.f;
}

void UPilotHUD_EP::SetLifeRendered(float life)
{
	renderedLifeInPercent = life;
}

float UPilotHUD_EP::GetLife()
{

	return renderedLifeInPercent / 100.f;
}
