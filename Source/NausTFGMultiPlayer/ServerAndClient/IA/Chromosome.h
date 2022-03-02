// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chromosome.generated.h"

UCLASS()
class NAUSTFGMULTIPLAYER_API AChromosome : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChromosome();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	virtual void Destroyed() override;

	FVector GetSizeGene();
	void SetSizeGene(FVector SizeGene);

	void ApplyFenotipe();
	void SetRandomGenes();

	void Mutation();

private:

	UPROPERTY(Replicated)
	FVector sizeGene;

	USceneComponent* root;

};
