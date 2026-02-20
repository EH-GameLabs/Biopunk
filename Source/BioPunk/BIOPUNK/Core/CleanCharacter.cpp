// Fill out your copyright notice in the Description page of Project Settings.


#include "BIOPUNK/Core/CleanCharacter.h"

// Sets default values
ACleanCharacter::ACleanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TargetingComponent = CreateDefaultSubobject<UTargetingComponent>(TEXT("TargetingComponent"));
}

void ACleanCharacter::ToggleTargetLock()
{
	if (TargetingComponent)
	{
		TargetingComponent->ToggleLock();
	}
}

void ACleanCharacter::DoLook(float Yaw, float Pitch)
{
	if (TargetingComponent->IsLocked()) return;
	
	Super::DoLook(Yaw, Pitch);
}
