// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "Monster.h"

ASword::ASword() {
	name = "Sword";
	damage = 10;
	radiusAttack = 50;

	// Создание компонента и привязка его к корневому компоненту
	SwordMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SwordMesh"));
	RootComponent = SwordMesh;

	// Загрузка меша для компонента
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Weapon_Pack/Skeletal_Mesh/SK_Sword.SK_Sword'"));
	if (MeshAsset.Succeeded())
	{
		SwordMesh->SetSkeletalMesh(MeshAsset.Object);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Меш загрузился"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Меш не загрузился"));
	}
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

USkeletalMeshComponent* ASword::GetMesh() {
	return SwordMesh;
}

void ASword::AttackNearbyEnemy() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("AttackNearbyEnemy"));
	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams Params(NAME_None, false, this);
	FCollisionObjectQueryParams ObjectParams(ECollisionChannel::ECC_Pawn);

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + FVector(0.f, 0.f, 1.f); // Регулируйте высоту конечной точки в зависимости от вашего мира

	bool bHit = GetWorld()->OverlapMultiByObjectType(Overlaps, StartLocation, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(radiusAttack), Params);

	if (bHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("if (bHit)"));
		for (const FOverlapResult& Overlap : Overlaps)
		{
			AMonster* Enemy = Cast<AMonster>(Overlap.GetActor());
			if (Enemy)
			{
				// Вызовите функцию TakeDamage() на противнике, чтобы нанести урон
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Красаучик, пизди черта"));
				Enemy->TakeDamage_Implementation(damage);
			}
		}
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