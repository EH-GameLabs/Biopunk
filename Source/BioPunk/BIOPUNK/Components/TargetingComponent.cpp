// Fill out your copyright notice in the Description page of Project Settings.


#include "BIOPUNK/Components/TargetingComponent.h"

#include "CombatEnemy.h"
#include "KismetTraceUtils.h"
#include "BIOPUNK/Interfaces/TargetableInterface.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UTargetingComponent::UTargetingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called every frame
void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CurrentTarget) return;
	
	ACombatEnemy* testEnemy = Cast<ACombatEnemy>(CurrentTarget);
	if (IsValid(testEnemy) && !testEnemy->CanTarget)
	{
		CurrentTarget = nullptr;
		DisableLock();
		return;
	}

	// --- VALIDATION PHASE ---
    
	// Check distance between Actors (Logic is fine here, we care about physical distance)
	float Dist = FVector::Dist(GetOwner()->GetActorLocation(), CurrentTarget->GetActorLocation());
	if (Dist > MaxLockDistance) 
	{
		DisableLock();
		return;
	}

	// --- ROTATION PHASE ---

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC && PC->PlayerCameraManager)
	{
		// Get current camera rotation
		FRotator CurrentRot = PC->GetControlRotation();
        
		// Get target location via Interface
		FVector TargetLoc = ITargetableInterface::Execute_GetTargetLocation(CurrentTarget);
        
		// BEST PRACTICE FIX: Calculate direction from CAMERA, not Actor
		// This prevents parallax errors when camera is offset from the character
		FVector CameraLoc = PC->PlayerCameraManager->GetCameraLocation();
		FVector Dir = TargetLoc - CameraLoc; 
		FRotator TargetRot = Dir.Rotation();

		// 3. Clampa il Pitch
		TargetRot.Pitch = FMath::Clamp(TargetRot.Pitch, MinPitch, MaxPitch);
		
		DrawDebugSphere(
			GetWorld(),
			TargetLoc,
			5,
			12,
			FColor::Red
		);

		// Optional: Keep the camera simpler by not forcing Roll (usually 0)
		TargetRot.Roll = 0.0f;

		// Interpolation
		// FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, LockRotationSpeed);
        
		PC->SetControlRotation(TargetRot);
	}
}

void UTargetingComponent::ToggleLock()
{
	if (CurrentTarget != nullptr)
	{
		CurrentTarget = nullptr;
		return;
	}
	
	CurrentTarget = FindBestTarget();
}

AActor* UTargetingComponent::FindBestTarget()
{
	// 1. Setup per SphereOverlap
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Visibility)); // O il tuo canale 'Enemy'
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	TArray<AActor*> OutActors;

	// 2. Trova tutti i potenziali target nel raggio
	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		GetOwner()->GetActorLocation(),
		SearchRadius,
		ObjectTypes,
		nullptr,
		ActorsToIgnore,
		OutActors
	);
	
	AActor* BestTarget = nullptr;
	float BestScore = -1.0f;

	FVector CamLoc;
	FRotator CamRot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(CamLoc, CamRot);
	FVector CamForward = CamRot.Vector();

	// 3. Itera e dai un punteggio
	for (AActor* Actor : OutActors)
	{
		if (!Actor->Implements<UTargetableInterface>()) continue;
		if (!ITargetableInterface::Execute_IsTargetable(Actor)) continue;
	
		FVector DirToTarget = (Actor->GetActorLocation() - CamLoc).GetSafeNormal();
		float DotProduct = FVector::DotProduct(CamForward, DirToTarget);
	
		if (DotProduct < 0.5f) continue;
        
		float Score = DotProduct; 
	
		if (Score > BestScore)
		{
			BestScore = Score;
			BestTarget = Actor;
		}
	}
	
	
	if (IsValid(BestTarget))
	{
		// Qui attiveresti l'icona UI sul target
		UE_LOG(LogTemp, Warning, TEXT("Check Target: %s"), BestTarget ? *BestTarget->GetName() : TEXT("NULL"));
		return BestTarget;
	}
	UE_LOG(LogTemp, Warning, TEXT("Check Target: %s"), BestTarget ? *BestTarget->GetName() : TEXT("NULL"));
	return nullptr;
}

void UTargetingComponent::DisableLock()
{
	CurrentTarget = nullptr;
}
