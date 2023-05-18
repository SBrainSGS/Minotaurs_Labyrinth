// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"


AMonster::AMonster(){
	targetEntity = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
};

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAI();
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	StartWander();
}

void AMonster::UpdateAI()
{
	{
		if (CanSeeTarget())
		{
			ChaseTarget();
			if (IsInRangeOfTarget())
			{
				AttackTarget();
			}
		}
		else
		{
			// Логика поиска новой цели или другие действия, если цель не видна
		}
	}
}

bool AMonster::CanSeeTarget(){
	FHitResult HitResult;
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = targetEntity->GetActorLocation();
	FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), false, this);
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams);
	return (HitResult.Actor == targetEntity);
}

void AMonster::ChaseTarget(){
	if (targetEntity)
	{
		StopWander();
		FVector TargetLocation = targetEntity->GetActorLocation();
		FVector Direction = TargetLocation - GetActorLocation();
		Direction.Normalize();

		FVector NewLocation = GetActorLocation() + Direction * movementSpeed * GetWorld()->DeltaTimeSeconds;
		SetActorLocation(NewLocation);
	}
}

void AMonster::AttackTarget()
{
	if (targetEntity)
	{
		FVector DamageOrigin = GetActorLocation(); // Позиция, откуда исходит урон
		FDamageEvent DamageEvent;
		targetEntity->TakeDamage(damage, FDamageEvent{}, nullptr, this);
	}
}

bool AMonster::IsInRangeOfTarget()
{
	FVector MonsterLocation = GetActorLocation();
	FVector TargetLocation = targetEntity->GetActorLocation();
	float DistanceSq = FVector::DistSquared(MonsterLocation, TargetLocation);
	return (DistanceSq <= FMath::Square(attackRadius));
}


void AMonster::StartWander()
{
	GetWorldTimerManager().SetTimer(WanderTimerHandle, this, &AMonster::StopWander, wanderDuration, false);

	FVector WanderLocation = GetActorLocation() + FVector(FMath::FRandRange(-1.0f, 1.0f), FMath::FRandRange(-1.0f, 1.0f), 0.0f).GetSafeNormal() * wanderRadius;

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), WanderLocation);
}

void AMonster::StopWander()
{
	GetWorldTimerManager().ClearTimer(WanderTimerHandle);
}