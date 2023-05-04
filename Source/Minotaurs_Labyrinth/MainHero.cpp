#include "MainHero.h"

AMainHero::AMainHero()
{
	//Отключение автоматической настройки поворота
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
	// Создание и настройка компонента коллизии (капсульная коллизия)
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	RootComponent = CollisionCapsule;
	
	//Создание скелета персонажа
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent ->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("SkeletalMesh'/Game/MainHero/Arissa.Arissa'"));

	// Создание и настройка компонента коллизии для взаимодействия (сферическая коллизия)
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	// Создание и настройка компонента камеры
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	// Настройка скорости движения персонажа
	MovementSpeed = 100.0f;

	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;

	// Создание и прикрепление компонента движения
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	// Настройка параметров движения
	FloatingPawnMovement->MaxSpeed = 500.0f;
	// Другие настройки движения...
}

void AMainHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Обработка поворота персонажа во время движения
	if (!FMath::IsNearlyZero(GetMovementComponent()->Velocity.SizeSquared()))
	{
		FRotator NewRotation = GetMovementComponent()->Velocity.ToOrientationRotator();
		SetActorRotation(NewRotation);
	}

}

void AMainHero::BeginPlay()
{
	Super::BeginPlay();

	// Получение контроллера персонажа
	AController* CharController = GetController();

	// Установка активной камеры
	if (CharController)
	{
		APlayerController* PlayerController = Cast<APlayerController>(CharController);
		if (PlayerController)
		{
			PlayerController->SetViewTarget(this);
		}
	}
}

void AMainHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Привязка функций к входным действиям персонажа
	PlayerInputComponent->BindAxis("MoveForwardBack", this, &AMainHero::MoveForwardBack);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AMainHero::MoveLeftRight);

	// Привязка функции к кнопке взаимодействия
	PlayerInputComponent->BindAction("Interaction w/ objects", IE_Pressed, this, &AMainHero::OnInteractionPressed);
}

void AMainHero::MoveForwardBack(float Value)
{
	if (Value != 0.0f)
	{
		// Определение направления движения вперед
		const FRotator Rotation = Controller->GetControlRotation();	
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Выполнение движения вперед
		AddMovementInput(Direction, Value);
	}
}

void AMainHero::MoveLeftRight(float Value)
{
	if (Value != 0.0f)
	{
		// Определение направления движения вправо
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Выполнение движения вправо
		AddMovementInput(Direction, Value);
	}
}

void AMainHero::OnInteractionPressed()
{
}



