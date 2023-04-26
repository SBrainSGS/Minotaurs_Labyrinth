#include "SpikeTrap.h"


ASpikeTrap::ASpikeTrap()
{
	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapMesh"));
	RootComponent = TrapMesh;

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
	if (OtherActor && OtherActor->Tags.Contains("Player"))
	{
	}
}
