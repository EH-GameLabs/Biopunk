// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventoryManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BIOPUNK_API UInventoryManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	int CurrentPotions = 0;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddPotion(int const PotionToAdd = 1) { CurrentPotions += PotionToAdd; }
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemovePotion(int const PotionToRemove = 1) { CurrentPotions -= PotionToRemove; }
};
