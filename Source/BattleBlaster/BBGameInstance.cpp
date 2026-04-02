// Fill out your copyright notice in the Description page of Project Settings.


#include "BBGameInstance.h"

#include "Kismet/GameplayStatics.h"


void UBBGameInstance::LoadNextLevel()
{
	int32 NextLevelIndex = CurrentLevelIndex + 1;
	
	if (NextLevelIndex <= LastLevelIndex)
		ChangeLevel(NextLevelIndex);
	else
	{
		RestartGame();
	}
}

void UBBGameInstance::RestartLevel()
{
	ChangeLevel(CurrentLevelIndex);
}

void UBBGameInstance::RestartGame()
{
	ChangeLevel(1);
}

void UBBGameInstance::ChangeLevel(int32 LevelIndex)
{
	if (LevelIndex >= 0 && LevelIndex <= LastLevelIndex)
	{
		CurrentLevelIndex = LevelIndex;
		
		FString LevelName = FString::Printf(TEXT("Level_%d"), CurrentLevelIndex);
		
		UGameplayStatics::OpenLevel(GetWorld(), *LevelName);
	}
}
