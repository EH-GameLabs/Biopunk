// Fill out your copyright notice in the Description page of Project Settings.


#include "BIOPUNK/Core/CPP_BiopunkCharacter.h"

#include "BIOPUNK/Components/TargetingComponent.h"

ACPP_BiopunkCharacter::ACPP_BiopunkCharacter()
{
	TargetingComponent = CreateDefaultSubobject<UTargetingComponent>(TEXT("TargetingComponent"));
}

void ACPP_BiopunkCharacter::ToggleTargetLock()
{
	if (TargetingComponent)
	{
		TargetingComponent->ToggleLock();
	}
}

void ACPP_BiopunkCharacter::DoLook(float Yaw, float Pitch)
{
	if (TargetingComponent->IsLocked()) return;
	
	Super::DoLook(Yaw, Pitch);
}
