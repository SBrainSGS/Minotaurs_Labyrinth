// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatHammer.h"

AGreatHammer::AGreatHammer() {
	name = "Great hammer";
	damage = 30;
	radiusAttack = 100;
	CooldownTime = 2.0f;
	Socket = "GreatHammerSocket";

	// �������� ���������� � �������� ��� � ��������� ����������
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AxeMesh"));
	RootComponent = SkeletalMesh;

	// �������� ���� ��� ����������
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Weapon_Pack/Skeletal_Mesh/SK_GreatHammer.SK_GreatHammer'"));
	if (MeshAsset.Succeeded())
	{
		SkeletalMesh->SetSkeletalMesh(MeshAsset.Object);
	}
}

void AGreatHammer::BeginPlay() {
	Super::BeginPlay();

	// �������� � ��������� ���������� ����
	SkeletalMesh = NewObject<USkeletalMeshComponent>(this, TEXT("AxeMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	SkeletalMesh->SetVisibility(true);
}

void AGreatHammer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// ��������� ��������� �� ��������� ����� ������
	UInputComponent* PlayerInputComponent = GetWorld()->GetFirstPlayerController()->InputComponent;

	// �������� ������� ���������� �����
	if (PlayerInputComponent)
	{
		// �������� ������� � ����������������� ����� (��������, ������� ������ ����)
		PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AGreatHammer::AttackNearbyEnemy);
	}
}