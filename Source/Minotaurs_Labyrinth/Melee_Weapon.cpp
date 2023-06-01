// Fill out your copyright notice in the Description page of Project Settings.


#include "Melee_Weapon.h"
#include "Monster.h"

AMelee_Weapon::AMelee_Weapon() {}

void AMelee_Weapon::AttackNearbyEnemy() {
	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams Params(NAME_None, false, this);
	FCollisionObjectQueryParams ObjectParams(ECollisionChannel::ECC_Pawn);

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + FVector(0.f, 0.f, 1.f); // Регулируйте высоту конечной точки в зависимости от вашего мира

	bool bHit = GetWorld()->OverlapMultiByObjectType(Overlaps, StartLocation, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(radiusAttack), Params);

	if(CanUseWeapon())
	{
		if (bHit)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("if (bHit)"));
			for (const FOverlapResult& Overlap : Overlaps)
			{
				AMonster* Enemy = Cast<AMonster>(Overlap.GetActor());
				if (Enemy)
				{
					// Вызовите функцию TakeDamage() на противнике, чтобы нанести урон
					Enemy->TakeDamage_Implementation(damage);
				}
			}
		}

		// Обновите время последнего использования оружия
		LastUsedTime = GetWorld()->GetTimeSeconds();
	}
}


bool AMelee_Weapon::CanUseWeapon() const
{
	float CurrentTime = GetWorld()->GetTimeSeconds();

	return (CurrentTime - LastUsedTime) >= CooldownTime;
}