// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotationComponent.generated.h"


class AActionPawn;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAUSTFGMULTIPLAYER_API URotationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	FRotator GetRotation();


	void ExecuteRotation(FRotator rotator);

	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_ExecuteRotation(FRotator rotator);

private:

	//UPROPERTY(Replicated)
	FRotator rotation;

};
