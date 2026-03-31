// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTower.h"

void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle FireTimerHandle;
	
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AEnemyTower::CheckFireCondition, FireRate, true);
}

void AEnemyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (InFireRange())
	{
		RotateTurret(PlayerTank->GetActorLocation());
	}
}

void AEnemyTower::CheckFireCondition()
{
	if (PlayerTank && InFireRange())
	{
		Fire();
	}
}

bool AEnemyTower::InFireRange()
{
	bool Result = false;
	
	if (PlayerTank)
	{
		float DistanceToTank = (GetActorLocation() - PlayerTank->GetActorLocation()).Size();
		Result = DistanceToTank <= Range;
	}
	
	return Result;
}
