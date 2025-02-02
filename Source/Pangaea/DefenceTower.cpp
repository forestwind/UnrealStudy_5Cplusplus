// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenceTower.h"

// Sets default values
ADefenceTower::ADefenceTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(_BoxComponent);

	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_MeshComponent->SetupAttachment(_BoxComponent);
}

// Called when the game starts or when spawned
void ADefenceTower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefenceTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ADefenceTower::GetHealthPoints()
{
	return _HealthPoints;
}

bool ADefenceTower::IsDestory()
{
	return (_HealthPoints > 0.0f);
}

bool ADefenceTower::CanFire()
{
	return (_ReloadCountingDown <= 0.0f);
}

