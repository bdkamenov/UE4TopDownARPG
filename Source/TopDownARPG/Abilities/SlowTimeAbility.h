// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Ability.h"
#include "SlowTimeAbility.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API USlowTimeAbility : public UAbility
{
	GENERATED_BODY()
	
public:
	virtual void Activate(AActor* Source) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASlowDownTimeProjectile> ProjectileClass;
	
};
