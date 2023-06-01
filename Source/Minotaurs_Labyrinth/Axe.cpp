// Fill out your copyright notice in the Description page of Project Settings.


#include "Axe.h"

AAxe::AAxe() {
	name = "Axe";
	damage = 30;
	radiusAttack = 100;
	CooldownTime = 1.5f;
	Socket = "Arm_Axe";

	// Создание компонента и привязка его к корневому компоненту
	AxeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AxeMesh"));
	RootComponent = AxeMesh;

	// Загрузка меша для компонента
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Weapon_Pack/Skeletal_Mesh/SK_GreatAxe.SK_GreatAxe'"));
	if (MeshAsset.Succeeded())
	{
		AxeMesh->SetSkeletalMesh(MeshAsset.Object);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Меш не загрузился"));
	}
}

void AAxe::BeginPlay() {
	Super::BeginPlay();

	// Создание и настройка компонента меча
	AxeMesh = NewObject<USkeletalMeshComponent>(this, TEXT("AxeMesh"));
	AxeMesh->SetupAttachment(RootComponent);
	AxeMesh->SetVisibility(true);
}

void AAxe::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// Получение указателя на компонент ввода игрока
	UInputComponent* PlayerInputComponent = GetWorld()->GetFirstPlayerController()->InputComponent;

	// Проверка наличия компонента ввода
	if (PlayerInputComponent)
	{
		// Привязка функции к пользовательскому вводу (например, нажатию кнопки мыши)
		PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AAxe::AttackNearbyEnemy);
	}
}