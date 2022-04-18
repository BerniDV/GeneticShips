// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameController.h"
#include "NausTFGMultiPlayer/Client/Controllers/VisualEffectsController.h"
#include "NausTFGMultiPlayer/Client/GUI/HUD/GameState/GameStateHUD_EP.h"
#include "NausTFGMultiPlayer/Client/GUI/HUD/GameState/HUDGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"

UActionGameController::UActionGameController()
{

	InitializeMenus();
}

void UActionGameController::InitializeMenus()
{

	ConstructorHelpers::FClassFinder <UGameStateHUD_EP> gameStateHUDClassBP(TEXT("/Game/Client/GUI/HUD/GameState/GameStateHUD_BP.GameStateHUD_BP_C"));
	GameStateHUDClass = gameStateHUDClassBP.Class;
}

void UActionGameController::Init(APlayerController* owner)
{
	actionPlayerController = Cast<AActionPlayerController>(owner);
}

void UActionGameController::CreaMenus()
{

	
	gameStateHUD = CreateWidget<UGameStateHUD_EP>(actionPlayerController, GameStateHUDClass);

	//Crea el controlador de efectos visuales, es actor ya que en objeto unreal anulaba las referencias de punteros por algun motivo
	visualEffectsController = GetWorld()->SpawnActor<AVisualEffectsController>();

}

void UActionGameController::BindSignals()
{
	
}

void UActionGameController::LoadHUD()
{
	
}

void UActionGameController::UnloadHUD()
{

	
}

void UActionGameController::UpdateHealth(float health)
{


}

void UActionGameController::LoadGameStateHUD()
{
	Super::LoadMenu(gameStateHUD);

}

void UActionGameController::UnloadGameStateHUD()
{
	Super::UnloadMenu(gameStateHUD);

}

void UActionGameController::SetRound(int round)
{
	if(gameStateHUD)
	{

		gameStateHUD->SetNumRound(round);
		gameStateHUD->UpdateNumRoundText();
	}
	
	
}

FString UActionGameController::GetRound()
{

	FString result = "";

	if(gameStateHUD)
	{

		result = gameStateHUD->GetNumRoundText();
	}

	return result; 
}

void UActionGameController::SetEnemiesAlive(int enemies)
{

	if (gameStateHUD)
	{

		gameStateHUD->SetEnemiesAlive(enemies);
		gameStateHUD->UpdateEnemiesAliveText();
	}

}

FString UActionGameController::GetEnemiesAliveText()
{
	FString result = "";

	if (gameStateHUD)
	{

		result = gameStateHUD->GetEnemiesAliveText();
	}

	return result;
}

void UActionGameController::SpawnParticlesAtLocation(FVector Location, FVector Scale)
{
	
	Super::SpawnParticlesAtLocation(Location, Scale);

}




