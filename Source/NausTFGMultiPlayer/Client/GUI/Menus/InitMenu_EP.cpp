// Fill out your copyright notice in the Description page of Project Settings.


#include "InitMenu_EP.h"

void UInitMenu_EP::OnClickAnyKey()
{

	signalOnClickAnyKey.Broadcast();
}
