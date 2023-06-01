#include "Monster.h"
#include "MainHero.h"
#include "NavigationSystem.h"
#include "AIController.h"

AMonster::AMonster()
{
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
    PawnSensingComponent->SetPeripheralVisionAngle(30.0f); // Угол обзора монстра
    PawnSensingComponent->SightRadius = 500.0f; // Радиус обзора монстра
    PawnSensingComponent->bSeePawns = true; // Включить обнаружение пешек
    IsPlayerSeen = false;
    attackDelay = 2.0f;
}

void AMonster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!targetEntity)
    {
        targetEntity = Cast<AMainHero>(GetWorld()->GetFirstPlayerController()->GetPawn());
    }
    else {
        AttackTarget();
    }
}


void AMonster::BeginPlay()
{
    Super::BeginPlay();
}

/*void AMonster::OnSeePawn(APawn* SeenPawn)
{
    AMainHero* Player = Cast<AMainHero>(SeenPawn);
    if (Player)
    {
        FString Message = TEXT("See");
        FColor Color = FColor::Green;
        float DisplayTime = 2.0f;
        GEngine->AddOnScreenDebugMessage(-1, DisplayTime, Color, Message);
        ChaseTarget();
        if (IsInRangeOfTarget())
        {
            Message = TEXT("Range");
            Color = FColor::Blue;
            DisplayTime = 2.0f;
            GEngine->AddOnScreenDebugMessage(-1, DisplayTime, Color, Message);
            AttackTarget();
        }
    }
}*/

/*void AMonster::ChaseTarget()
{
    if (targetEntity)
    {
        StopWander();

        FString Message = TEXT("Chasing");
        FColor Color = FColor::Red;
        float DisplayTime = 2.0f;
        GEngine->AddOnScreenDebugMessage(-1, DisplayTime, Color, Message);

        FVector TargetLocation = targetEntity->GetActorLocation();

        AAIController* AIController = Cast<AAIController>(GetController());
        if (AIController)
        {
            AIController->MoveToLocation(TargetLocation);

            FRotator TargetRotation = (TargetLocation - GetActorLocation()).Rotation();
            SetActorRotation(TargetRotation);
        }
        FVector Direction = targetEntity->GetActorLocation() - GetActorLocation();
        Direction.Z = 0.0f; // Устанавливаем Z-координату в 0, чтобы игнорировать высоту

        // Нормализуем вектор направления
        Direction.Normalize();

        // Вычисляем угол поворота к цели
        FRotator TargetRotation = Direction.Rotation();

        // Устанавливаем новую ориентацию поворота противника
        SetActorRotation(TargetRotation);

        // Двигаемся вперед в направлении цели
        FVector ForwardVector = GetActorForwardVector();
        FVector NewLocation = GetActorLocation() + ForwardVector * movementSpeed * GetWorld()->GetDeltaSeconds();

        SetActorLocation(NewLocation);
    }
}*/

void AMonster::AttackTarget()
{
    // Определить положение монстра
    FVector MonsterLocation = GetActorLocation();

    // Создать сферу с центром в положении монстра и радиусом обнаружения
    FSphere SphereDetectionSphere(MonsterLocation, attackRadius);

    // Массив для хранения обнаруженных актеров
    TArray<AActor*> OverlappingActors;

    // Поиск актеров внутри сферы
    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        MonsterLocation,
        attackRadius,
        TArray<TEnumAsByte<EObjectTypeQuery>>(),
        AMainHero::StaticClass(),
        TArray<AActor*>(),
        OverlappingActors
    );

    // Проверка наличия обнаруженных актеров
    if (OverlappingActors.Num() > 0)
    {
        if (CanAttack())
        {
            // Обнаружен главный герой в радиусе
            targetEntity->TakeDamage(damage);
            lastAttack = GetWorld()->GetTimeSeconds();
        }
    }
}

bool AMonster::CanAttack() const
{
    float CurrentTime = GetWorld()->GetTimeSeconds();
    return (CurrentTime - lastAttack) >= attackDelay;
}

bool AMonster::IsInRangeOfTarget()
{
    FVector MonsterLocation = GetActorLocation();
    FVector TargetLocation = targetEntity->GetActorLocation();
    FVector HorizontalDirection = FVector(TargetLocation.X, TargetLocation.Y, MonsterLocation.Z);
    float DistanceSq = FVector::DistSquared2D(MonsterLocation, HorizontalDirection);
    return (DistanceSq <= FMath::Square(attackRadius));
}

void AMonster::StartWander()
{
    GetWorldTimerManager().SetTimer(WanderTimerHandle, this, &AMonster::StopWander, wanderDuration, false);

    FVector WanderLocation = GetActorLocation() + FVector(FMath::FRandRange(-1.0f, 1.0f), FMath::FRandRange(-1.0f, 1.0f), 0.0f).GetSafeNormal() * wanderRadius;

    AAIController* AIController = Cast<AAIController>(GetController());
    if (AIController)
    {
        AIController->MoveToLocation(WanderLocation);
    }
}
    
void AMonster::StopWander()
{
    GetWorldTimerManager().ClearTimer(WanderTimerHandle);
}