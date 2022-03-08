// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/Factories/ReferencePawnsFactory.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/ActionGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Chromosome.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Controllers/EnemyManager.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Controllers/GeneticManager.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerControllerImpl.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerStates/ActionPlayerState.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"

AActionGameMode::AActionGameMode()
{

	DefaultPawnClass = nullptr;
	PlayerStateClass = AActionPlayerState::StaticClass();
	PlayerControllerClass = AActionPlayerController::StaticClass();
	GameStateClass = AActionGameState::StaticClass();
	
}


FString AActionGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueNetId,
	const FString& Options, const FString& Portal)
{

	int teamIdTest = 1;

	MatchOptions matchOptions(Options, teamIdTest);

	AActionPlayerController* playerController = Cast<AActionPlayerController>(NewPlayerController);

	playerController->Initialize(matchOptions);

	return Super::InitNewPlayer(playerController, UniqueNetId, Options, Portal);
	
}


UClass* AActionGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{

	AActionPlayerController* myController = Cast<AActionPlayerController>(InController);

	if (myController)
	{
		UClass* pawn = myController->GetDefaultPawn();

		if(pawn)
		{

			return pawn;

		}
		
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}


void AActionGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if(! playersInGame.Find(NewPlayer->GetUniqueID()))
	{

		playersInGame.Add(NewPlayer->GetUniqueID(), NewPlayer);
	}

	SetTeam(NewPlayer);

}

void AActionGameMode::BeginPlay()
{
	Super::BeginPlay();

	geneticManager = GetWorld()->SpawnActor<AGeneticManager>();
	enemyManager = GetWorld()->SpawnActor<AEnemyManager>();

	Cast<AActionGameState>(GameState)->signalPlayerDead.AddDynamic(this, &AActionGameMode::EndGame);
	GetWorld()->GetTimerManager().SetTimer(timerHandler, this, &AActionGameMode::SetUpFirstGeneration, 10.f, false);
}

void AActionGameMode::SetTeam(APlayerController* PlayerController)
{

	AActionPlayerController* PC = Cast<AActionPlayerController>(PlayerController);

	int teamId = PC->GetTeamId();

	for (auto x : GameState->PlayerArray)
	{
		//Si no somos nosotros mismos y somos del mismo equipo nos asignamos como compañero
		if (x->GetPlayerId() != PlayerController->GetPlayerState<AActionPlayerState>()->GetPlayerId() && Cast<AActionPlayerState>(x)->GetTeamID() == teamId)
		{

			AActionPawn* teamMate = Cast<AActionPawn>(x->GetPawn());

			//nos lo asignamos como compañero
			PC->GetPlayerControllerImpl()->SetTeamMate(teamMate);

			AActionPlayerController* PCTeamMate = Cast<AActionPlayerController>(teamMate->GetOwner());

			//Nos asignamos como compañero
			AActionPawn* myPawn = Cast<AActionPawn>(PlayerController->GetPawn());
			PCTeamMate->GetPlayerControllerImpl()->SetTeamMate(myPawn);
		}
	}
}

void AActionGameMode::EndGame()
{
	
	GetWorld()->ServerTravel("/Game/Levels/MenuLevels/MainMenuLevel");
}

TArray<AChromosome*> AActionGameMode::SetUpNextGeneration(TArray<AChromosome*> actualGeneration)
{


	TArray<AChromosome*> nextGeneration = geneticManager->GenerateNextGenerationDna(actualGeneration);
	DestroyGeneration(actualGeneration);

	return nextGeneration;
	
}

void AActionGameMode::SetUpFirstGeneration()
{

	TArray<AChromosome*> firstGeneration = geneticManager->GenerateFirstGenerationDna();

	roundResultFuture = enemyManager->SpawnGeneration(firstGeneration);

	GetWorld()->GetTimerManager().ClearTimer(timerHandler);
	GetWorld()->GetTimerManager().SetTimer(timerHandler, this, &AActionGameMode::ProcesEndRound, 20.f, false);
}

void AActionGameMode::InitializeNextRound()
{

	AActionGameState* gameState = Cast<AActionGameState>(GameState);

	int currentRound = gameState->GetRound();
	currentRound++;

	gameState->SetRound(currentRound);
}

void AActionGameMode::DestroyGeneration(TArray<AChromosome*> &generation)
{

	for (auto x : generation)
	{

		x->Destroy();
	}

	generation.Empty();
}

void AActionGameMode::ProcesEndRound()
{

	UE_LOG(LogTemp, Warning, TEXT("End Round"));
	GetWorld()->GetTimerManager().ClearTimer(timerHandler);
	InitializeNextRound();
}

void AActionGameMode::ProcesNewRound(TArray<AChromosome*>& newGeneration)
{

	UE_LOG(LogTemp, Warning, TEXT("New Round"));
	roundResultFuture = enemyManager->SpawnGeneration(newGeneration);
	GetWorld()->GetTimerManager().ClearTimer(timerHandler);
	GetWorld()->GetTimerManager().SetTimer(timerHandler, this, &AActionGameMode::ProcesEndRound, 20.f, false);
}

void AActionGameMode::ProcesBetweenRounds(TArray<AChromosome*> actualGenerationresult)
{
	UE_LOG(LogTemp, Warning, TEXT("Between Rounds"));
	TArray<AChromosome*> nextGeneration;

	//Se supone que aqui hacemos procesos como calcular siguiente generacion o poner cuenta atras etc...
	nextGeneration = SetUpNextGeneration(actualGenerationresult);

	FTimerDelegate timerDel;
	timerDel.BindUFunction(this, FName("ProcesNewRound"), nextGeneration);

	GetWorld()->GetTimerManager().SetTimer(timerHandler, timerDel, 5.f, false);

	//ProcesNewRound(nextGeneration);

}

void AActionGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(roundResultFuture._Is_ready())
	{
		
		TArray<AChromosome*> actualGenerationresult = roundResultFuture.get();
		ProcesBetweenRounds(actualGenerationresult);
	}
}
