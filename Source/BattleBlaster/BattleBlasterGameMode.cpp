// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"

#include "EnemyTower.h"
#include "Kismet/GameplayStatics.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize enemy tower count
	TArray<AActor*> EnemyTowers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyTower::StaticClass(), EnemyTowers);
	TowerCount = EnemyTowers.Num();
	
	UE_LOG(LogTemp, Display, TEXT("Number of Enemies Set To %d"), TowerCount);


	// Initialize player tank
	if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		PlayerTank = Cast<APlayerTank>(PlayerPawn);
		
		if (!PlayerTank)
		{
			UE_LOG(LogTemp, Error, TEXT("Player Pawn is not a Player Tank"));
		}
	}
	
	for (AActor* EnemyTower : EnemyTowers)
	{
		if (AEnemyTower* CastEnemyTower = Cast<AEnemyTower>(EnemyTower))
		{
			CastEnemyTower->PlayerTank = PlayerTank;
				
			UE_LOG(LogTemp, Display, TEXT("Player tank assigned to enemy tower(%s)"), *EnemyTower->GetActorNameOrLabel());
		}
	}


	
	
}
