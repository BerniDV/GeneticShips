// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundsController.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"

// Sets default values
ASoundsController::ASoundsController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*
	ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (DefaultExplosionEffect.Succeeded())
	{
		explosionSound = DefaultExplosionEffect.Object;
	}
	*/

	ConstructorHelpers::FObjectFinder<USoundCue> ShootSound(TEXT("SoundCue'/Game/Assets/Sounds/LaserShot/laserShot.laserShot'"));
	ConstructorHelpers::FObjectFinder<USoundCue> bulletImpactSound(TEXT("SoundCue'/Game/Assets/Sounds/LaserShot/bulletImpacteCue.bulletImpacteCue'"));
	ConstructorHelpers::FObjectFinder<USoundCue> explosionSound(TEXT("SoundCue'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));
	ConstructorHelpers::FObjectFinder<USoundCue> spaceAmbient(TEXT("SoundCue'/Game/Assets/Sounds/Space/Ambient/SpaceAmbientCue.SpaceAmbientCue'"));
	ConstructorHelpers::FObjectFinder<USoundCue> mainMenuMusic(TEXT("SoundCue'/Game/Assets/Sounds/Menu/MainMenu/mainMenuMusicCue.mainMenuMusicCue'"));

	if (ShootSound.Succeeded())
	{
		sounds[(int8)Sounds::Shoot] = ShootSound.Object;
		sounds[(int8)Sounds::BulletImpact] = bulletImpactSound.Object;
		sounds[(int8)Sounds::Explosion] = explosionSound.Object;
		sounds[(int8)Sounds::SpaceAmbient] = spaceAmbient.Object;
		sounds[(int8)Sounds::MainMenuMusic] = mainMenuMusic.Object;
	}
	
}

// Called when the game starts or when spawned
void ASoundsController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoundsController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASoundsController::SpawnSoundAtLocation(FVector Location, Sounds sound, FRotator Rotation, float VolumeMultiplier)
{

	
	 
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sounds[(int8)sound], Location, Rotation, VolumeMultiplier, 1, 0, shotAttenuation);
	
}

