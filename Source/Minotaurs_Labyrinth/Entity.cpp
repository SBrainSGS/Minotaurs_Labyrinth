#include "Entity.h"

AEntity::AEntity()
{
	// Создание и настройка компонента коллизии (капсульная коллизия)
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	RootComponent = CollisionCapsule;
	
	//Создание скелета персонажа
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent ->SetupAttachment(RootComponent);
	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEntity::TakeDamage_Implementation(float DamageAmount)
{
	if(health - DamageAmount > 0)
	{
		health -= (DamageAmount - defence);
		FString Message = TEXT("Attacked");
		FColor Color = FColor::Red;
		float DisplayTime = 2.0f;
		GEngine->AddOnScreenDebugMessage(-1, DisplayTime, Color, Message);
	} else Destroy();
}

