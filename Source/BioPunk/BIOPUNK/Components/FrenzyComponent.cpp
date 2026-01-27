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
	
}

// Called every frame
void UFrenzyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	GEngine->AddOnScreenDebugMessage(
		67,
		2.0f,
		FColor::Red,
		FString::Printf(TEXT("%d: %.2f"), BarIndex, BarValue)
	);
	
	// TODO: 
	// anche gli altri valori sono moltiplicati dal DecreaseMultiplier?
	DecreaseBar(DeltaTime * BarStats[BarIndex].DecreaseMultiplier);
}

void UFrenzyComponent::IncreaseBar(const float Value)
{
	if (IsInDebuff) return;
	
	// GEngine->AddOnScreenDebugMessage(
	// 	-1,
	// 	2.0f,
	// 	FColor::Red,
	// 	FString::Printf(TEXT("Hitler"))
	// );
	
	// TODO:
	// teniamo i valori di scarto? 
	// oppure quando si passa da una barra all'altra si parte sempre da 0?
	
	const float IncreaseValue = Value * BarStats[BarIndex].IncreaseMultiplier;
	
	// BarValue = FMath::Min(BarValue + IncreaseValue, 1.0f); 
	BarValue += IncreaseValue;
	
	const float Scarto = FMath::Max(BarValue - 1, 0.0f);
	
	// Check Bar
	if (BarValue >= 1.0f)
	{
		if (BarIndex == 2)
		{
			HasReachedMax = true;
			BarValue = 1;
		}
		else
		{
			BarIndex++;
			BarValue = Scarto;
		}
	}
}

void UFrenzyComponent::DecreaseBar(const float Value)
{
	
	BarValue = FMath::Max(BarValue - Value, 0.0f);
	
	if (BarIndex == 0) return;
	
	if (BarValue <= 0.0f)
	{
		// if (BarIndex == 2)
		// {
		if (HasReachedMax)
		{
			HasReachedMax = false;
			StartDebuff();
		}
		// }
		else
		{
			BarIndex--;
			BarValue = 1.0f;
		}
	}
}

void UFrenzyComponent::StartDebuff()
{
	IsInDebuff = true;
	
	// TODO: 
	// da capire
	BarIndex = 0;
	
	// movimento più lento ?
	
	// subisci più danni ?
	
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
	
	// movimento torna normale ?
	
	// subisci danni normali ?
}
