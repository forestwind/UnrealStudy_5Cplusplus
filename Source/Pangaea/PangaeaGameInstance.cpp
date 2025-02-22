// Fill out your copyright notice in the Description page of Project Settings.


#include "PangaeaGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UPangaeaGameInstance::StartListenServer()
{
	UE_LOG(LogTemp, Warning, TEXT("StartListenServer"));

	auto world = GEngine->GetCurrentPlayWorld();
	UGameplayStatics::OpenLevel(world, "TopDownMap", true, "?listen");
}

void UPangaeaGameInstance::JoinAsClient(FString IPAddress)
{
	UE_LOG(LogTemp, Warning, TEXT("JoinAsClient"));

	auto world = GEngine->GetCurrentPlayWorld();
	UGameplayStatics::OpenLevel(world, *IPAddress, true, "?join");
}


void UPangaeaGameInstance::LeaveGame()
{
	UE_LOG(LogTemp, Warning, TEXT("LeaveGame"));

	auto world = GEngine->GetCurrentPlayWorld();
	UGameplayStatics::OpenLevel(world, "LobbyMap");
}

void UPangaeaGameInstance::CastFail()
{
	UE_LOG(LogTemp, Warning, TEXT("CastFail"));
}
