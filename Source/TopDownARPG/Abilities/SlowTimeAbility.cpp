// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowTimeAbility.h"
#include "Projectiles/SlowDownTimeProjectile.h"
#include "TopDownARPG.h"
#include "Engine/World.h"


void USlowTimeAbility::Activate(AActor* Source)
{
	Super::Activate(Source);

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("USlowTimeAbility::Activate IsValid(World) == false"));
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Source;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = Source->GetActorLocation() + Source->GetActorForwardVector() * -400.0f;

	AActor* Projectile = World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, Source->GetActorRotation(), SpawnParameters);
	if (IsValid(Projectile) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("USlowTimeAbility::Activate IsValid(Projectile) == false"));
		return;
	}
}