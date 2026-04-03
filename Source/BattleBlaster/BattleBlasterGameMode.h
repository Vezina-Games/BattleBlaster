// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "PlayerTank.h"
#include "ScreenMessage.h"

#include "BattleBlasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ABattleBlasterGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenMessage> ScreenMessageClass;
	
	UScreenMessage* ScreenMessageWidget;
	
	
	UPROPERTY(EditAnywhere)
	float GameOverTime = 5.0f;
	
	UPROPERTY(EditAnywhere)
	int32 CountdownDelay = 3.0f;
	
	int32 CountdownTimer;
	
	FTimerHandle CountdownTimerHandle;
	
	UPROPERTY(VisibleAnywhere)
	bool IsGameOver;
	UPROPERTY(VisibleAnywhere)
	bool IsVictory;
	
	APlayerTank* PlayerTank;
	int32 TowerCount;
	
	void ActorDied(AActor* Actor);
	void OnGameOverTimerTimeout();
	void OnCountdownTimerTimeout();
	
	
	
};
