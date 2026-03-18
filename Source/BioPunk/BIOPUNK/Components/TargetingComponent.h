// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class BIOPUNK_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTargetingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ToggleLock();

protected:
	UPROPERTY(EditAnywhere, Category="Targeting")
	float SearchRadius = 2000.f;

	UPROPERTY(EditAnywhere, Category="Targeting")
	float MaxLockDistance = 3000.f;
	
	UPROPERTY(EditAnywhere, Category="Targeting")
	float LockRotationSpeed = 5.0f;
	
	UPROPERTY(EditAnywhere, Category="Targeting")
	float MinPitch = -10.0f; // Limite guardando in basso
	
	UPROPERTY(EditAnywhere, Category="Targeting")
	float MaxPitch = 45.0f;  // Limite guardando in alto 

	// Riferimento al target attuale
	UPROPERTY(BlueprintReadOnly, Category="Targeting")
	AActor* CurrentTarget;

private:
	AActor* FindBestTarget();
	void DisableLock();
	void UpdateRotationSettings(bool locked);
	
public:
	bool IsLocked() const {return CurrentTarget != nullptr;}
};
