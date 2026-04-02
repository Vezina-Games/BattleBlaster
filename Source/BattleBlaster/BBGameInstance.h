// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BBGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API UBBGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere)
	int32 LastLevelIndex = 3;
	
	UPROPERTY(VisibleAnywhere)
	int32 CurrentLevelIndex = 1;
	
	void LoadNextLevel();
	void RestartLevel();
	void RestartGame();
	
private:
	void ChangeLevel(int32 LevelIndex);
	
	
};
