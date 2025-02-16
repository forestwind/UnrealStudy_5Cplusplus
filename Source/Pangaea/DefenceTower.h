// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DefenceTower.generated.h"

UCLASS(Blueprintable)
class PANGAEA_API ADefenceTower : public AActor
{
	GENERATED_BODY()
	
public:	
	ADefenceTower();

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	int HealthPoints = 500;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	int ShellDefense = 3;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	float AttackRange = 6.0f;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	float ReloadInterval = 1.0f;

protected:
	virtual void BeginPlay() override;
	
	UClass* _FireballClass;

	int _HealthPoints; // 타워의 현재 생명 포인트
	float _ReloadCountingDown;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defence Tower", meta = (DisplayName = "GetHP"))
	//UFUNCTION(BlueprintPure, Category = "Pangaea|Defence Tower", meta = (DisplayName = "GetHP"))
	int GetHealthPoints();

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defence Tower")
	//UFUNCTION(BlueprintPure, Category = "Pangaea|Defence Tower")
	bool IsDestory();

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defence Tower")
	//UFUNCTION(BlueprintPure, Category = "Pangaea|Defence Tower")
	bool CanFire();

	void Fire();
	void Hit(int damage);

protected:
	void DestroyProcess();

	class APlayerAvatar* _Target = nullptr;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = "true"))
	USphereComponent* _SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* _MeshComponent;

public:
	FORCEINLINE USphereComponent* GetSphereComponent() const
	{
		return _SphereComponent;
	}

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const
	{
		return _MeshComponent;
	}
};
