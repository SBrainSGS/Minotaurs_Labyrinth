// Fill out your copyright notice in the Description page of Project Settings.


#include "Axe.h"

AAxe::AAxe() {
	name = "Axe";
	damage = 30;
	radiusAttack = 100;
	CooldownTime = 1.5f;
	Socket = "Arm_Axe";

	// �������� ���������� � �������� ��� � ��������� ����������
	AxeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AxeMesh"));
	RootComponent = AxeMesh;

	// �������� ���� ��� ����������
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Weapon_Pack/Skeletal_Mesh/SK_GreatAxe.SK_GreatAxe'"));
	if (MeshAsset.Succeeded())
	{
		AxeMesh->SetSkeletalMesh(MeshAsset.Object);
	}
}

void AAxe::BeginPlay() {
	Super::BeginPlay();

	// �������� � ��������� ���������� ����
	AxeMesh = NewObject<USkeletalMeshComponent>(this, TEXT("AxeMesh"));
	AxeMesh->SetupAttachment(RootComponent);
	AxeMesh->SetVisibility(true);
}

void AAxe::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// ��������� ��������� �� ��������� ����� ������
	UInputComponent* PlayerInputComponent = GetWorld()->GetFirstPlayerController()->InputComponent;

	// �������� ������� ���������� �����
	if (PlayerInputComponent)
	{
		// �������� ������� � ����������������� ����� (��������, ������� ������ ����)
		PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AAxe::AttackNearbyEnemy);
	}
}