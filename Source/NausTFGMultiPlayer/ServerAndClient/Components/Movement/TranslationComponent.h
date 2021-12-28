// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TranslationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAUSTFGMULTIPLAYER_API UTranslationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTranslationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	void MoveForward(float movement);

	void MoveRight(float movement);

	UFUNCTION(Server, Unreliable, WithValidation)
	void MoveForward_Server(FVector movement);

	UFUNCTION(Server, Unreliable, WithValidation)
	void MoveRight_Server(FVector movement);


private:

	UFUNCTION()
	void ApplyMovement();

	UPROPERTY(replicatedUsing = ApplyMovement)
	FVector position;

	float movementSpeedInCm;
		
};
