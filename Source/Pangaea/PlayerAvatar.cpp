// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAvatar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerAvatarAnimInstance.h"


// Sets default values
APlayerAvatar::APlayerAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	auto characterMovement = GetCharacterMovement();
	characterMovement->bOrientRotationToMovement = true; // Rotate character to moving direction
	characterMovement->RotationRate = FRotator(0.f, 640.f, 0.f);
	characterMovement->bConstrainToPlane = true;
	characterMovement->bSnapToPlaneAtStart = true;

	_springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_springArmComponent->SetupAttachment(RootComponent);		
	_springArmComponent->SetUsingAbsoluteRotation(true);		
	_springArmComponent->TargetArmLength = 800.f;				 
	_springArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	_springArmComponent->bDoCollisionTest = false;


	_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_cameraComponent->SetupAttachment(_springArmComponent, USpringArmComponent::SocketName);
	_cameraComponent->bUsePawnControlRotation = false;  
}

// Called when the game starts or when spawned
void APlayerAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto animInst = Cast<UPlayerAvatarAnimInstance>(GetMesh()->GetAnimInstance());
	animInst->Speed = GetCharacterMovement()->Velocity.Size2D();
	UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), animInst->Speed);
}

// Called to bind functionality to input
void APlayerAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int APlayerAvatar::GetHealthPoints()
{
	return _HealthPoints;
}

bool APlayerAvatar::IsKilled()
{
	return (_HealthPoints <= 0.0f);
}

bool APlayerAvatar::CanAttack()
{
	return (_AttackCountingDown <= 0.0f);
}

