// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTower.h"

void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (PlayerTank)
	{
		FVector TowersLocation = GetActorLocation();
		FVector PlayerLocation = PlayerTank->GetActorLocation();
		
		float DistanceToTank = (TowersLocation - PlayerLocation).Size();
		
		if (DistanceToTank <= Range)
		{
			FVector LookAtTarget = PlayerLocation;
		
			RotateTurret(LookAtTarget);
		}
		
		
		
	}
	
}
