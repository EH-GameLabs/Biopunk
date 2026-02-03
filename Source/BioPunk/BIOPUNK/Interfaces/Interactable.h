// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BIOPUNK/Core/CPP_BiopunkCharacter.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BIOPUNK_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// immagino sia solamente il player ad interagire
	// quindi prendo direttamente il puntatore al character
	
	// general version to call in c++
	void Interact(AActor* Interactor) { NativeInteract(Interactor); }

	// activate to implement in c++
	virtual void NativeInteract(AActor* Interactor)
	{
		UObject* Object = Cast<UObject>(this);
		Execute_BP_Interact(Object, Interactor);
	}

	// ===== Functions to implement =====
	// activate to implement in blueprint
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interactable")
	void BP_Interact(AActor* Interactor);
};
