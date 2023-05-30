// Fill out your copyright notice in the Description page of Project Settings.


#include "Melee_Weapon.h"

AMelee_Weapon::AMelee_Weapon() {}

void AMelee_Weapon::slash() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Нанесен урон"));
}