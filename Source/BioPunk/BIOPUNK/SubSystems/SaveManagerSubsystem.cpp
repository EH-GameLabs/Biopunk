// Fill out your copyright notice in the Description page of Project Settings.


#include "BIOPUNK/SubSystems/SaveManagerSubsystem.h"

void USaveManagerSubsystem::SaveGame_Implementation()
{
	
}

void USaveManagerSubsystem::LoadGame_Implementation()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Red,
		FString::Printf(TEXT("LoadGame_Implementation"))
	);
}

class UWorld* USaveManagerSubsystem::GetWorld() const
{
	const UGameInstance* GameInstance = GetGameInstance();

	if (GameInstance)
	{
		return GameInstance->GetWorld();
	}

	return nullptr;
}

void USaveManagerSubsystem::CreateNewSave_Implementation()
{
	
}

void USaveManagerSubsystem::DeleteSave_Implementation(FName SlotName)
{
	
}

void USaveManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	ReceiveInitialize();
}
