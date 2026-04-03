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
	if (PlayerTank && PlayerTank->IsAlive && InFireRange())
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
		
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			GetActorLocation(),
			PlayerTank->GetActorLocation(),
			ECC_Visibility
		);
		
		Result = (HitResult.GetActor() == PlayerTank) && DistanceToTank <= Range;
	}
	
	return Result;
}

void AEnemyTower::HandleDestruction()
{
	Super::HandleDestruction();
	
	Destroy();
}
