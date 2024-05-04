// Fill out your copyright notice in the Description page of Project Settings.


#include "Melee_Weapon.h"
#include "Monster.h"

AMelee_Weapon::AMelee_Weapon() {}

void AMelee_Weapon::AttackNearbyEnemy() {
	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams Params(NAME_None, false, this);
	FCollisionObjectQueryParams ObjectParams(ECollisionChannel::ECC_Pawn);

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + FVector(0.f, 0.f, 1.f); // ����������� ������ �������� ����� � ����������� �� ������ ����

	bool bHit = GetWorld()->OverlapMultiByObjectType(Overlaps, StartLocation, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(radiusAttack), Params);

	if(CanUseWeapon())
	{
		if (bHit)
		{
			for (const FOverlapResult& Overlap : Overlaps)
			{
				AEntity* Enemy = Cast<AEntity>(Overlap.GetActor());
				if (Enemy)
				{
					// �������� ������� TakeDamage() �� ����������, ����� ������� ����
					Enemy->TakeDamage_Implementation(damage);
				}
			}
		}

		// �������� ����� ���������� ������������� ������
		LastUsedTime = GetWorld()->GetTimeSeconds();
	}
}


bool AMelee_Weapon::CanUseWeapon() const
{
	float CurrentTime = GetWorld()->GetTimeSeconds();

	return (CurrentTime - LastUsedTime) >= CooldownTime;
}