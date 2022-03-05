// Fill out your copyright notice in the Description page of Project Settings.


#include "VisualEffectsController.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AVisualEffectsController::AVisualEffectsController()
{


	ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (DefaultExplosionEffect.Succeeded())
	{
		explosionEffect = DefaultExplosionEffect.Object;
	}

	ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultFireEffect(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (DefaultFireEffect.Succeeded())
	{
		fireEffect = DefaultFireEffect.Object; 
	}


}

void AVisualEffectsController::SpawnParticlesAtLocation(FVector Location, FVector Scale)
{
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionEffect, Location, FRotator::ZeroRotator, Scale, true, EPSCPoolMethod::None);
}

void AVisualEffectsController::SpawnFollowingParticles(USceneComponent* AttatchTo, FVector Scale)
{

		UGameplayStatics::SpawnEmitterAttached(fireEffect, AttatchTo, NAME_None, FVector(ForceInit), FRotator::ZeroRotator, Scale, EAttachLocation::KeepRelativeOffset, true, EPSCPoolMethod::None, true);
}
