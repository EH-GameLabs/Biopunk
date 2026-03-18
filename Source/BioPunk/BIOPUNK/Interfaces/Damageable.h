// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BIOPUNK_API IDamageable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// ===== TAKE DAMAGE =====
	// TakeDamage general version to call in c++
	void TakeDamage(AActor* Interactor, float Damage) { NativeTakeDamage(Interactor, Damage); }

	// TakeDamage to implement in c++
	virtual void NativeTakeDamage(AActor* Interactor, float Damage)
	{
		UObject* Object = Cast<UObject>(this);
		Execute_BP_TakeDamage(Object, Interactor, Damage);
	}

	// TakeDamage to implement in blueprint
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Damageable")
	void BP_TakeDamage(AActor* Interactor, float Damage);
	
	
	// ===== DIE =====
	// Die general version to call in c++
	UFUNCTION()
	virtual void Die() { NativeDie(); }

	// Die to implement in c++
	virtual void NativeDie()
	{
		BP_Die();
	}

	// Die to implement in blueprint
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Damageable")
	void BP_Die();
};
