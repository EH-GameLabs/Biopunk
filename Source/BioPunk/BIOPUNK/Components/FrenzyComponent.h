// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FrenzyComponent.generated.h"

USTRUCT(BlueprintType)
struct FBarData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IncreaseMultiplier = 1.0f;
	
	// ===== BUFF =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageMultiplier = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasCombo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasAbility;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFrenzyBarChanged, int, index);
UCLASS( ClassGroup=(Custom), Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent) )
class BIOPUNK_API UFrenzyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFrenzyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FrenzyComponent")
	TArray<FBarData> BarStats;
	
	int8 BarIndex = 0;
	float BarValue = 0.0f; // DA 0 A 1 --> SEMPRE
	// bool HasReachedMax;
	bool IsInDebuff;
	bool IsInCombat; // TODO: spostare in un manager (Combat Manager ?)
	bool IsLastPhaseActive;
	FTimerHandle TimerHandle_Debuff;
	
	// RECHARGE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FrenzyComponent|RECHARGE")
	float IncreaseBarOnHit = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FrenzyComponent|RECHARGE")
	float IncreaseBarOnPerfectDodge = 0.3f;
	
	// DISCHARGE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FrenzyComponent|DISCHARGE")
	float DecreaseBarOnTime = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FrenzyComponent|DISCHARGE")
	float DecreaseBarOnTakeDamage = 0.07f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FrenzyComponent|DISCHARGE")
	float DecreaseBarOnAbilityUse = 0.6f;
	
	// -------------- DEBUFF --------------------
	// barra non si ricarica per “rechargeTime” sec
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FrenzyComponent|Debuff")
	float StopRechargeTime; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FrenzyComponent|Debuff")
	float DebuffDamageTakenMultiplier = 1.0f;
	
	
	UFUNCTION(BlueprintCallable, Category="FrenzyComponent")
	void IncreaseBar(const float Value);
	UFUNCTION(BlueprintCallable, Category="FrenzyComponent")
	void DecreaseBar(const float Value);
	
	void StartDebuff();
	void EndDebuff();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintAssignable, Category="FrenzyComponent")
	FOnFrenzyBarChanged OnBarChangedDelegate;
	
	UFUNCTION(BlueprintCallable, Category="FrenzyComponent")
	void BarChanged(int index);
	
};
