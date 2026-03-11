// Fill out your copyright notice in the Description page of Project Settings.


#include "BIOPUNK/Components/FrenzyComponent.h"

// Sets default values for this component's properties
UFrenzyComponent::UFrenzyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
	// ...
}


// Called when the game starts
void UFrenzyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OnBarChangedDelegate.AddDynamic(this, &UFrenzyComponent::BarChanged);
}

// Called every frame
void UFrenzyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (BarIndex != 2 || !IsLastPhaseActive) return;
	DecreaseBar(DeltaTime * DecreaseBarOnTime);
}

void UFrenzyComponent::BarChanged(int index)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Black,
		FString::Printf(TEXT("New bar index: %d"), index)
	);
}

void UFrenzyComponent::ActivateLastPhase_Implementation()
{
	if (BarIndex != 2 || IsLastPhaseActive) return;
	
	IsLastPhaseActive = true;
	OnDamageMultiplierChanged.Broadcast(DebuffDamageTakenMultiplier);
}

void UFrenzyComponent::IncreaseBar(const float Value)
{
	if (IsInDebuff) return;
	
	const float IncreaseValue = Value * BarStats[BarIndex].IncreaseMultiplier;
	BarValue += IncreaseValue;
	
	const float Scarto = FMath::Max(BarValue - 1, 0.0f);
	
	// Check Bar
	if (Scarto <= 0.0f) return;
	
	if (BarIndex == 2)
	{
		BarValue = 1;
	}
	else
	{
		BarIndex++;
		OnBarChangedDelegate.Broadcast(BarIndex);
		BarValue = Scarto;
	}
}

void UFrenzyComponent::DecreaseBar(const float Value)
{
	BarValue = FMath::Max(BarValue - Value, 0.0f);
	
	if (BarIndex == 0) return;
	
	if (BarValue <= 0.0f)
	{
		if (IsLastPhaseActive)
		{
			StartDebuff();
		}
		else
		{
			BarIndex--;
			BarValue = 1.0f;
		}
		
		OnBarChangedDelegate.Broadcast(BarIndex);
	}
}

void UFrenzyComponent::StartDebuff()
{
	IsLastPhaseActive = false;
	IsInDebuff = true;
	
	BarIndex = 0;
	BarValue = 0;
	OnBarChangedDelegate.Broadcast(BarIndex);
	
	// subisci più danni
	OnDamageMultiplierChanged.Broadcast(DebuffDamageTakenMultiplier);
	
	// RESET
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(TimerHandle_Debuff))
	{
		TimerManager.ClearTimer(TimerHandle_Debuff);
	}

	TimerManager.SetTimer(
		TimerHandle_Debuff,
		this,
		&UFrenzyComponent::EndDebuff,
		StopRechargeTime,
		false
	);
}

void UFrenzyComponent::EndDebuff()
{
	IsInDebuff = false;
	
	// subisci danni normali
	OnDamageMultiplierChanged.Broadcast(1);
}
