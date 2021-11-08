// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkyBoxActor.h"
#include "MainMenuSkyBox_EP.generated.h"

UCLASS()
class NAUSTFGMULTIPLAYER_API AMainMenuSkyBox_EP : public ASkyBoxActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainMenuSkyBox_EP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
