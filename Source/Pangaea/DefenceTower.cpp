// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenceTower.h"
#include "PlayerAvatar.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADefenceTower::ADefenceTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(_SphereComponent);
	_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADefenceTower::OnBeginOverlap);
	_SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ADefenceTower::OnEndOverlap);

	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_MeshComponent->SetupAttachment(_SphereComponent);

	static ConstructorHelpers::FObjectFinder<UBlueprint> blueprint_finder(TEXT("Blueprint'/Game/TopDown/Blueprints/BP_Fireball.BP_Fireball'"));
	_FireballClass = (UClass*)blueprint_finder.Object->GeneratedClass;
}

// Called when the game starts or when spawned
void ADefenceTower::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(0.5f);
}

// Called every frame
void ADefenceTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_Target != nullptr)
	{
		Fire();
	}
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

void ADefenceTower::Fire()
{
	auto fireball = Cast<AProjectile>(GetWorld()->SpawnActor(_FireballClass));

	FVector startLocation = GetActorLocation();
	startLocation.Z += 100.0f;
	FVector targetLocation = _Target->GetActorLocation();
	targetLocation.Z = startLocation.Z;
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(startLocation, targetLocation);
	fireball->SetActorLocation(startLocation);
	fireball->SetActorRotation(rotation);
}

void ADefenceTower::DestroyProcess()
{
}

void ADefenceTower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("OnBeginOverlap"));

	APlayerAvatar* player = Cast<APlayerAvatar>(OtherActor);

	if (player)
	{
		_Target = player;

		UE_LOG(LogTemp, Log, TEXT("OnBeginOverlap checkPlayer"));
	}
}

void ADefenceTower::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("OnEndOverlap"));

	if (_Target != nullptr && OtherActor == _Target)
	{
		_Target = nullptr;
	}
}

