// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BaseAI.generated.h"

// This class does not need to be modified.
UINTERFACE(blueprintable)
class UBaseAI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BIOPUNK_API IBaseAI
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
protected:
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = BaseAI)
	bool GetPatrolStatus();
};
