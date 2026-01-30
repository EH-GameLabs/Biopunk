// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BIOPUNK_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public: 
	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void MainMenu();
	
	UFUNCTION(BlueprintCallable)
	void GameOverMenu();
	
	UFUNCTION(BlueprintCallable)
	void WinMenu();
};
void UMyGameInstance::StartGame()
{
	UGameplayStatics::OpenLevel(this, FName("Lvl_ThirdPerson"));
}

void UMyGameInstance::MainMenu()
{
	UGameplayStatics::OpenLevel(this, FName("Lvl_MainMenu"));
}

void UMyGameInstance::GameOverMenu()
{
	UGameplayStatics::OpenLevel(this, FName("Lvl_GameOverMenu"));
}

void UMyGameInstance::WinMenu()
{
	UGameplayStatics::OpenLevel(this, FName("Lvl_WinMenu"));
}
