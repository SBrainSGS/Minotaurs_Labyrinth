#include "MainHero.h"

#include "Misc/OutputDeviceNull.h"

AMainHero::AMainHero()
{
	//Установка значений здоровья, маны и защиты
	health = 100;
	mana = 100;
	defence = 0;
	
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

	InteractingActor = nullptr;
}

void AMainHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Обработка поворота персонажа во время движения
	if (!FMath::IsNearlyZero(GetMovementComponent()->Velocity.SizeSquared()))
        {
            FRotator CurrentRotation = GetActorRotation();
            FRotator TargetRotation = GetMovementComponent()->Velocity.ToOrientationRotator();
            FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 10);
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
	
	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMainHero::OnInteractionSphereBeginOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AMainHero::OnInteractionSphereEndOverlap);
}

void AMainHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Привязка функций к входным действиям персонажа
	PlayerInputComponent->BindAxis("MoveForwardBack", this, &AMainHero::MoveForwardBack);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AMainHero::MoveLeftRight);

	// Привязка функции к кнопке взаимодействия
	PlayerInputComponent->BindAction("Interaction w/ objects", IE_Pressed, this, &AMainHero::OnInteractionPressed);

	//Привязка событий перекрытия компонента
	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMainHero::OnInteractionSphereBeginOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AMainHero::OnInteractionSphereEndOverlap);
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
	if (InCollision && InteractingActor)
	{
		TArray<FString> EmptyArgs; // Пустой массив аргументов
		FOutputDeviceNull ar; // Пустой вывод аргументов
		
		InteractingActor->CallFunctionByNameWithArguments(TEXT("Interact"), ar, nullptr, true); // Вызываем функцию "Interact" непосредственно из объекта взаимодействия
	}
}

void AMainHero::OnInteractionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InteractingActor = OtherActor; // Сохраняем указатель на объект, с которым происходит перекрытие
	InCollision = true;
}

void AMainHero::OnInteractionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == InteractingActor) // Проверяем, если объект, с которым произошло перекрытие, является текущим объектом взаимодействия
		{
		InteractingActor = nullptr; // Сбрасываем указатель, поскольку объект больше не находится в перекрытии
		InCollision = false;
		}
}

void AMainHero::TakeDamage_Implementation(float DamageAmount)
{
	if(health - DamageAmount > 0)
	{
		health -= (DamageAmount - defence) ;
		FString Message = TEXT("Damage");
		FColor Color = FColor::Green;
		float DisplayTime = 2.0f;
		GEngine->AddOnScreenDebugMessage(-1, DisplayTime, Color, Message);
	}
}
