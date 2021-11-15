// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"

UCustomGameInstance::UCustomGameInstance()
{


}

void UCustomGameInstance::SetRoleSelected(NausTFGRolTypes_Enum Role)
{

	roleSelected = Role;
}

NausTFGRolTypes_Enum UCustomGameInstance::GetRoleSelected()
{

	return roleSelected;
}
