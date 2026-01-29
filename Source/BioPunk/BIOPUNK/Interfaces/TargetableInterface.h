// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UTargetableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BIOPUNK_API ITargetableInterface
{
	GENERATED_BODY()

public:
	// Permette di dire se l'oggetto è "lockabile" (es. non è morto, non è invisibile)
	UFUNCTION(BlueprintNativeEvent)
	bool IsTargetable() const; 
    
	// Punto specifico dove mirare (es. il petto o la testa, non i piedi)
	UFUNCTION(BlueprintNativeEvent)
	FVector GetTargetLocation() const;
};
