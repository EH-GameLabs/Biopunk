// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BIOPUNK_API USaveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	// UFUNCTION(BlueprintCallable, Category = "SaveManagerSubsystem")
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveManagerSubsystem")
	void SaveGame();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveManagerSubsystem")
	void LoadGame();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveManagerSubsystem")
	void CreateNewSave();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveManagerSubsystem")
	void DeleteSave(FName SlotName);
	
	UFUNCTION(BlueprintCallable, Category = "SaveManagerSubsystem")
	virtual UWorld* GetWorld() const override;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On Subsystem Initialized"), Category = "SaveSystem|Lifecycle")
	void ReceiveInitialize();
};
