// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BioPunkCharacter.h"
#include "BIOPUNK/Components/TargetingComponent.h"
#include "GameFramework/Character.h"
#include "CleanCharacter.generated.h"

UCLASS()
class BIOPUNK_API ACleanCharacter : public ABioPunkCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACleanCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTargetingComponent* TargetingComponent;

	UFUNCTION(BlueprintCallable, Category="Combat")
	void ToggleTargetLock();
	
	virtual void DoLook(float Yaw, float Pitch) override;

};
