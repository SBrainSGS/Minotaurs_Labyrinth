// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "Monster.h"

ASword::ASword() {
	name = "Sword";
	damage = 10;
	radiusAttack = 50;

	// �������� ���������� � �������� ��� � ��������� ����������
	SwordMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SwordMesh"));
	RootComponent = SwordMesh;

	// �������� ���� ��� ����������
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Weapon_Pack/Skeletal_Mesh/SK_Sword.SK_Sword'"));
	if (MeshAsset.Succeeded())
	{
		SwordMesh->SetSkeletalMesh(MeshAsset.Object);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("��� ����������"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("��� �� ����������"));
	}
}

void ASword::BeginPlay() {
	Super::BeginPlay();
	
	// �������� � ��������� ���������� ����
	SwordMesh = NewObject<USkeletalMeshComponent>(this, TEXT("SwordMesh"));
	SwordMesh->SetupAttachment(RootComponent);
	SwordMesh->SetVisibility(true);
}

void ASword::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// ��������� ��������� �� ��������� ����� ������
	UInputComponent* PlayerInputComponent = GetWorld()->GetFirstPlayerController()->InputComponent;

	// �������� ������� ���������� �����
	if (PlayerInputComponent)
	{
		// �������� ������� � ����������������� ����� (��������, ������� ������ ����)
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
	FVector EndLocation = StartLocation + FVector(0.f, 0.f, 1.f); // ����������� ������ �������� ����� � ����������� �� ������ ����

	bool bHit = GetWorld()->OverlapMultiByObjectType(Overlaps, StartLocation, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(radiusAttack), Params);

	if (bHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("if (bHit)"));
		for (const FOverlapResult& Overlap : Overlaps)
		{
			AMonster* Enemy = Cast<AMonster>(Overlap.GetActor());
			if (Enemy)
			{
				// �������� ������� TakeDamage() �� ����������, ����� ������� ����
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("���������, ����� �����"));
				Enemy->TakeDamage_Implementation(damage);
			}
		}
	}
}

//void ASword::Attack() {
//	// ��������, ����� �� ��� ��������� � ������ ������ (��������, �������� �� ����������� ��� ��������� ��������)
//	if (CanAttack())
//	{
//		// ����������� ����� ����
//		StartAttackAnimation();
//		ApplyDamageToEnemies();
//	}
//}
//
//bool ASword::CanAttack() const {
//	// �������������� ������ ��������, ����� �� ��� ��������� � ������ ������
//	// ��������, �������� �� �����������, ��������� �������� ��� ������ �������
//	// ������� true, ���� ��� ����� ���������, � false � ��������� ������
//	return true;
//}
//
//void ASword::StartAttackAnimation() {
//	// ����� �� ������ ��������� �������� ����� ����
//	// ��������, ��������������� ������������ �������� ��� ��������� ��������� ��������
//}
//
//void ASword::ApplyDamageToEnemies() {
//	// ����� �� ������ ����������� ������ ��������� ����� ������
//	// ��������, ����������� ���� ������ � ������� ��������� ���� � ��������� �� �����
//}

//void ASword::SetSwordTexture(UTexture* Texture) {
//	// ��������� ������� ���������� ����
//	if (SwordMesh)
//	{
//		// �������� �������� ����
//		UMaterialInstanceDynamic* DynamicMaterial = SwordMesh->CreateDynamicMaterialInstance(0);
//
//		// ������������� �������� � ��������
//		if (DynamicMaterial)
//		{
//			DynamicMaterial->SetTextureParameterValue("TextureBlend", Texture);
//		}
//	}
//}