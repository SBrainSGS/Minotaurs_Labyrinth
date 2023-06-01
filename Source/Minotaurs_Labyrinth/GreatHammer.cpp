// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatHammer.h"

AGreatHammer::AGreatHammer() {
	name = "Great hammer";
	damage = 30;
	radiusAttack = 100;
	CooldownTime = 2.0f;
	Socket = "GreatHammerSocket";

	// Создание компонента и привязка его к корневому компоненту
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AxeMesh"));
	RootComponent = SkeletalMesh;

	// Загрузка меша для компонента
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Weapon_Pack/Skeletal_Mesh/SK_GreatHammer.SK_GreatHammer'"));
	if (MeshAsset.Succeeded())
	{
		SkeletalMesh->SetSkeletalMesh(MeshAsset.Object);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Меш не загрузился"));
	}
}

void AGreatHammer::BeginPlay() {
	Super::BeginPlay();

	// Создание и настройка компонента меча
	SkeletalMesh = NewObject<USkeletalMeshComponent>(this, TEXT("AxeMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	SkeletalMesh->SetVisibility(true);
}

void AGreatHammer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// Получение указателя на компонент ввода игрока
	UInputComponent* PlayerInputComponent = GetWorld()->GetFirstPlayerController()->InputComponent;

	// Проверка наличия компонента ввода
	if (PlayerInputComponent)
	{
		// Привязка функции к пользовательскому вводу (например, нажатию кнопки мыши)
		PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AGreatHammer::AttackNearbyEnemy);
	}
}