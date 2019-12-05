// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownARPGCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TopDownARPG.h"

#include "SlowDownTimeProjectile.h"


// Sets default values
ASlowDownTimeProjectile::ASlowDownTimeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTopDownARPG, Error, TEXT("ASlowDownTimeProjectile::ASlowDownTimeProjectile"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComponent->SetGenerateOverlapEvents(true);

	//SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	RootComponent = SphereComponent;

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASlowDownTimeProjectile::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ASlowDownTimeProjectile::OnOverlapOver);


	OnOverlapParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	OnOverlapParticle->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ASlowDownTimeProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ASlowDownTimeProjectile::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTopDownARPG, Error, TEXT("ASlowDownTimeProjectile::OnOverlap"));


	if (IsValid(OnOverlapParticle))
	{
		OnOverlapParticle->ActivateSystem();
	}

	ATopDownARPGCharacter* Character = Cast<ATopDownARPGCharacter>(Other);
	if (IsValid(Character))
	{
		Character->CustomTimeDilation = TimeDilation;
	}
	
}

void ASlowDownTimeProjectile::OnOverlapOver(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTopDownARPG, Error, TEXT("ASlowDownTimeProjectile::OnOverlapOver"));

	ATopDownARPGCharacter* Character = Cast<ATopDownARPGCharacter>(Other);
	if (IsValid(Character))
	{
		Character->CustomTimeDilation = 1.f;
	}

	if (Destroy() == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("Projectile is indestructable"));
	}
}

// Called every frame
void ASlowDownTimeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

