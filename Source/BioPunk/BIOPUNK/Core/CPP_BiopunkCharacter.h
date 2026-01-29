// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Variant_Combat/CombatCharacter.h"
#include "CPP_BiopunkCharacter.generated.h"

class UTargetingComponent;
/**
 * 
 */
UCLASS()
class BIOPUNK_API ACPP_BiopunkCharacter : public ACombatCharacter
{
	GENERATED_BODY()
	ACPP_BiopunkCharacter();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTargetingComponent* TargetingComponent;

	UFUNCTION(BlueprintCallable, Category="Combat")
	void ToggleTargetLock();
	
	virtual void DoLook(float Yaw, float Pitch) override;
};
