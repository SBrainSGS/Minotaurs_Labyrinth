#include "SpikeTrap.h"

#include "Misc/OutputDeviceNull.h"


ASpikeTrap::ASpikeTrap()
{
	damage = 10;
	
	ObjectCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ObjectCollisionComponent"));
	RootComponent = ObjectCollisionComponent;

	//Создание скелета ловушки
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent ->SetupAttachment(RootComponent);

	TriggerCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerCollisionComponent"));
	TriggerCollisionComponent->SetupAttachment(RootComponent);
	TriggerCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::OnTrapTriggered);
}

void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();
	// Дополнительная инициализация или логика начала игры
}

void ASpikeTrap::OnTrapTriggered(
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
			AEntity* MainHero = Cast<AEntity>(OtherActor);
			if (MainHero)
			{
				// Вызываем метод TakeDamage у персонажа
				MainHero->TakeDamage(damage);
			}
		}
	}
}
