#include "DefenceTower.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerAvatar.h"
#include "Projectile.h"
#include "weapon.h"
#include "PangaeaGameMode.h"

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

void ADefenceTower::BeginPlay()
{
	Super::BeginPlay();

	_SphereComponent->SetSphereRadius(AttackRange);
	SetActorTickInterval(ReloadInterval);
	_PangaeaGameMode = Cast<APangaeaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ADefenceTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_Target != nullptr && GetNetMode() != NM_Client)
	{
		Fire();
	}
}

int ADefenceTower::GetHealthPoints()
{
	return _HealthPoints;
}

bool ADefenceTower::IsDestroyed()
{
	return (_HealthPoints > 0.0f);
}

bool ADefenceTower::CanFire()
{
	return (_ReloadCountingDown <= 0.0f);
}

void ADefenceTower::Fire()
{
	//auto fireball = Cast<AProjectile>(GetWorld()->SpawnActor(_FireballClass));
	auto fireball = _PangaeaGameMode->SpawnOrGetFireball(_FireballClass);

	FVector startLocation = GetActorLocation();
	startLocation.Z += 100.0f;
	FVector targetLocation = _Target->GetActorLocation();
	targetLocation.Z = startLocation.Z;
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(startLocation, targetLocation);
	fireball->SetActorLocation(startLocation);
	fireball->SetActorRotation(rotation);
}


void ADefenceTower::Hit(int damage)
{
}

void ADefenceTower::DestroyProcess()
{

}

void ADefenceTower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	APlayerAvatar* player = Cast<APlayerAvatar>(OtherActor);

	if (player)
	{
		_Target = player;
	}
}


void ADefenceTower::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex)
{
	if (_Target != nullptr && OtherActor == _Target)
	{
		_Target = nullptr;
	}
}

void ADefenceTower::OnMeshBeginOverlap(AActor* OtherActor)
{
	/*AWeapon* weapon = Cast<AWeapon>(OtherActor);
	if (weapon == nullptr || weapon->Holder == nullptr)
	{
		return;
	}

	APangaeaCharacter* character = weapon->Holder;
	if (character->IsA(APlayerAvatar::StaticClass()) &&
		character->IsAttacking() &&
		weapon->IsWithinAttackRange(character->AttackRange, this) &&
		CanBeDamaged())
	{
		Hit(weapon->Holder->Strength);
	}*/
}