#include "DartTrap.h"

ADartTrap::ADartTrap()
{
	DartDamage = 4;
	
	ObjectCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ObjectCollisionComponent"));
	RootComponent = ObjectCollisionComponent;

	//Создание скелета ловушки
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent ->SetupAttachment(RootComponent);

	TriggerCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerCollisionComponent"));
	TriggerCollisionComponent->SetupAttachment(RootComponent);
	TriggerCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADartTrap::OnTrapTriggered);
}

void ADartTrap::BeginPlay()
{
	Super::BeginPlay();
	// Добавьте здесь код, который должен быть выполнен при начале игры (BeginPlay) для DartTrap
}

void ADartTrap::OnTrapTriggered(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	// Проверяем, является ли объект OtherActor персонажем с тегом "Player"
	if (OtherActor->Implements<UCommunicator_Interface>())
	{
		if (OtherActor->IsA<AMainHero>())
		{
			AMainHero* MainHero = Cast<AMainHero>(OtherActor);
			if (MainHero)
			{
				// Вызываем метод TakeDamage у персонажа
				MainHero->TakeDamage(DartDamage);
			}
		}
	}
}