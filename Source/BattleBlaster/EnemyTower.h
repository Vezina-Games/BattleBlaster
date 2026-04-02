// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

#include "PlayerTank.h"

#include "EnemyTower.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API AEnemyTower : public ABasePawn
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	APlayerTank* PlayerTank;
	
	void CheckFireCondition();
	bool InFireRange();
	void HandleDestruction();
	
	UPROPERTY(EditAnywhere)
	float Range = 1000.0f;
	UPROPERTY(EditAnywhere)
	float FireRate = 2.0f;
	UPROPERTY(EditAnywhere)
	float ReloadTime = 3.0f;
	float NextFireTime;
};
