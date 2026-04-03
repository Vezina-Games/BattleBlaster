// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"

#include "BBGameInstance.h"
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
	
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		ScreenMessageWidget = CreateWidget<UScreenMessage>(PlayerController, ScreenMessageClass);
		if (ScreenMessageWidget)
		{
			ScreenMessageWidget->AddToPlayerScreen();
			ScreenMessageWidget->SetMessageText("GET READY!");
		}
	}
	
	CountdownTimer = CountdownDelay;
	
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ABattleBlasterGameMode::OnCountdownTimerTimeout, 1.0f, true);
	
}

void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{
	
	if (DeadActor == PlayerTank)
	{
		// Player Has Died
		PlayerTank->HandleDestruction();
		IsGameOver = true;
	}
	else
	{
		// Tower Has Died
		if (AEnemyTower* DeadTower = Cast<AEnemyTower>(DeadActor))
		{
			DeadTower->HandleDestruction();
			
			TowerCount--;
			if (TowerCount <= 0)
			{
				UE_LOG(LogTemp, Display, TEXT("All towers destroyed"));
				IsGameOver = true;
				IsVictory = true;
			}
		}
		
	}
	if (IsGameOver)
	{
		FString VictoryMessage = IsVictory ? "VICTORY!" : "DEFEAT!";
		ScreenMessageWidget->SetMessageText(VictoryMessage);
		
		FTimerHandle GameOverTimer;
		GetWorld()->GetTimerManager().SetTimer(GameOverTimer, this, &ABattleBlasterGameMode::OnGameOverTimerTimeout, GameOverTime, false);
		
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ABattleBlasterGameMode::OnGameOverTimerTimeout()
{
	if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld()))
	{
		if (UBBGameInstance* BBGameInstance = Cast<UBBGameInstance>(GameInstance))
		{
			if (IsVictory)
			{
				BBGameInstance->LoadNextLevel();
			}
			else
			{
				BBGameInstance->RestartLevel();
			}
		}
	}
}

void ABattleBlasterGameMode::OnCountdownTimerTimeout()
{
	CountdownTimer--;
	
	if (CountdownTimer > 0)
	{
		ScreenMessageWidget->SetMessageText(FString::FromInt(CountdownTimer));
	}
	else if (CountdownTimer == 0)
	{
		ScreenMessageWidget->SetMessageText("GO!");
		PlayerTank->SetPlayerEnabled(true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
}
