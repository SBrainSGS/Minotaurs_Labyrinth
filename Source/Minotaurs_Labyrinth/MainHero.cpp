#include "MainHero.h"

AMainHero::AMainHero()
{
	// Создание и настройка компонента коллизии (капсульная коллизия)
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	RootComponent = CollisionCapsule;

	// Создание и настройка компонента коллизии для взаимодействия (сферическая коллизия)
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);

	// Создание и настройка компонента отображения меша персонажа
	CharacterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetupAttachment(RootComponent);

	//Создание скелета персонажа
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = SkeletalMeshComponent;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("SkeletalMesh'/Game/MainHero/Arissa.Arissa'"));
	if (SkeletalMeshAsset.Succeeded())
	{
		SkeletalMeshComponent->SetSkeletalMesh(SkeletalMeshAsset.Object);
	}

	// Установка анимационного синтезатора
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBlueprint(TEXT("AnimBlueprint'/Game/MainHero/Animations/BPA_MainHero.BPA_MainHero'"));
	if (AnimBlueprint.Succeeded())
	{
		MainHeroAnimBlueprint = AnimBlueprint.Object;
	}

	// Создание и настройка компонента Spring Arm для управления камерой
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	CameraSpringArm->TargetArmLength = 500.f;
	CameraSpringArm->bEnableCameraLag = false;
	CameraSpringArm->bEnableCameraRotationLag = false;
	CameraSpringArm->bInheritPitch = false;
	CameraSpringArm->bInheritYaw = false;
	CameraSpringArm->bInheritRoll = false;

	// Создание и настройка компонента камеры
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	// Настройка скорости движения персонажа
	MovementSpeed = 500.0f;
}

void AMainHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Обработка логики движения персонажа
	// ...

	// Обработка логики вращения камеры
	FRotator CameraRotation = CameraSpringArm->GetComponentRotation();
	CameraRotation.Pitch = 0.f; // Ограничение вращения камеры только по Y-оси
	CameraSpringArm->SetWorldRotation(CameraRotation);
}

void AMainHero::BeginPlay()
{
	Super::BeginPlay();
}

void AMainHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Привязка функций к входным действиям персонажа
	PlayerInputComponent->BindAxis("MoveForwardBack", this, &AMainHero::MoveForwardBack);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AMainHero::MoveLeftRight);
}

void AMainHero::MoveForwardBack(float Value)
{
	if (Value != 0.0f)
	{
		// Определение направления движения вперед
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Выполнение движения вперед
		AddMovementInput(Direction, Value * MovementSpeed);

		// Вращение персонажа в сторону движения
		FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(Direction);
		SetActorRotation(NewRotation);
	}
}

void AMainHero::MoveLeftRight(float Value)
{
	if (Value != 0.0f)
	{
		// Определение направления движения вправо
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Выполнение движения вправо
		AddMovementInput(Direction, Value * MovementSpeed);

		// Вращение персонажа в сторону движения
		FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(Direction);
		SetActorRotation(NewRotation);
	}
}