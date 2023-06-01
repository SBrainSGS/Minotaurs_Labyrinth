// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "Monster.h"

ASword::ASword() {
	name = "Sword";
	damage = 10;
	radiusAttack = 100;
	CooldownTime = 0.5f;
	Socket = "Arm_Weapon";

	// Создание компонента и привязка его к корневому компоненту
	SwordMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SwordMesh"));
	RootComponent = SwordMesh;

	// Загрузка меша для компонента
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Weapon_Pack/Skeletal_Mesh/SK_Sword.SK_Sword'"));
	if (MeshAsset.Succeeded())
	{
		SwordMesh->SetSkeletalMesh(MeshAsset.Object);
	}
	/*else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Меш не загрузился"));
	}*/
}

void ASword::BeginPlay() {
	Super::BeginPlay();
	
	// Создание и настройка компонента меча
	SwordMesh = NewObject<USkeletalMeshComponent>(this, TEXT("SwordMesh"));
	SwordMesh->SetupAttachment(RootComponent);
	SwordMesh->SetVisibility(true);
}

void ASword::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// Получение указателя на компонент ввода игрока
	UInputComponent* PlayerInputComponent = GetWorld()->GetFirstPlayerController()->InputComponent;

	// Проверка наличия компонента ввода
	if (PlayerInputComponent)
	{
		// Привязка функции к пользовательскому вводу (например, нажатию кнопки мыши)
		PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ASword::AttackNearbyEnemy);
	}
}

//void ASword::Attack() {
//	// Проверка, может ли меч атаковать в данный момент (например, проверка на перезарядку или состояние анимации)
//	if (CanAttack())
//	{
//		// Инициируйте атаку меча
//		StartAttackAnimation();
//		ApplyDamageToEnemies();
//	}
//}
//
//bool ASword::CanAttack() const {
//	// Дополнительная логика проверки, может ли меч атаковать в данный момент
//	// Например, проверка на перезарядку, состояние анимации или другие факторы
//	// Верните true, если меч может атаковать, и false в противном случае
//	return true;
//}
//
//void ASword::StartAttackAnimation() {
//	// Здесь вы можете запустить анимацию атаки меча
//	// Например, воспроизведение определенной анимации или установка состояния анимации
//}
//
//void ASword::ApplyDamageToEnemies() {
//	// Здесь вы можете реализовать логику нанесения урона врагам
//	// Например, обнаружение всех врагов в области поражения меча и нанесение им урона
//}

//void ASword::SetSwordTexture(UTexture* Texture) {
//	// Проверяем наличие компонента меча
//	if (SwordMesh)
//	{
//		// Получаем материал меча
//		UMaterialInstanceDynamic* DynamicMaterial = SwordMesh->CreateDynamicMaterialInstance(0);
//
//		// Устанавливаем текстуру в материал
//		if (DynamicMaterial)
//		{
//			DynamicMaterial->SetTextureParameterValue("TextureBlend", Texture);
//		}
//	}
//}