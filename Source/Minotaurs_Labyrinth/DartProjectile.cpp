#include "DartProjectile.h"

ADartProjectile::ADartProjectile()
{
	// Установка корневого компонента
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Инициализация компонента SphereCollision
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetSphereRadius(10.0f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECC_WorldDynamic);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Инициализация компонента ProjectileMovement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	// Настройка параметров по умолчанию
	Damage = 10.0f;
	Target = nullptr;
}

void ADartProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Подписываемся на событие пересечения коллизии
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ADartProjectile::OnProjectileOverlap);
}

void ADartProjectile::OnProjectileOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	// Проверяем, является ли пересекаемый объект целью
	if (OtherActor == Target)
	{
		// Проверяем, является ли объект целью с тегом "Player"
		if (OtherActor->IsA<AMainHero>())
		{
			AMainHero* MainHero = Cast<AMainHero>(OtherActor);
			if (MainHero)
			{
				// Наносим урон персонажу
				MainHero->TakeDamage(Damage);
			}
		}

		// Уничтожаем себя после попадания
		Destroy();
	}
}

void ADartProjectile::Launch(const FVector& LaunchVelocity)
{
	// Запускаем себя в указанном направлении и скорости
	ProjectileMovement->Velocity = LaunchVelocity;
}