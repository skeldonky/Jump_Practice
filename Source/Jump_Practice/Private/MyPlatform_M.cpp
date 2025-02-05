// Fill out your copyright notice in the Description page of Project Settings.

#include <cmath>

#include "MyPlatform_M.h"

// Sets default values
AMyPlatform_M::AMyPlatform_M()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Component
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	// Mesh, Material
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Cabin_Lake/Meshes/Modules/SM_Modules_plank_01.SM_Modules_plank_01"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Cabin_Lake/Materials/MI_Wood_Kit.MI_Wood_Kit"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	BaseLocation = FVector(0, MoveSpeed, 0);
}

// Called when the game starts or when spawned
void AMyPlatform_M::BeginPlay()
{
	Super::BeginPlay();

	// �ǹ��� ���� �߾����� �̵�
	MovePivotToCenter();
	
	//�����ؾ� 0, 0, 0 �� �ƴϴ�(�����ڿ� ������ 0, 0, 0)
	StartLocation = GetActorLocation();

	// ���� ���� (�ӵ� ��� �� ���)
	Direction = Direction.GetSafeNormal();
}

// Called every frame
void AMyPlatform_M::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
}

void AMyPlatform_M::MovePlatform(float DeltaTime)
{
	// ���� ��ġ ��������
	FVector CurrentLocation = GetActorLocation();

	// �̵� �Ÿ� ���
	FVector NewLocation = CurrentLocation + Direction * MoveSpeed * DeltaTime;

	// ���� ��ġ�κ����� �̵� �Ÿ� ���
	float TraveledDistance = FVector::Dist(StartLocation, NewLocation);

	// �ִ� �Ÿ� �ʰ� �� ���� ����
	if (TraveledDistance >= MaxRange || TraveledDistance <= 0.0f)
	{
		// ���� ����
		Direction *= -1;

		// �պ��� ���� �̵� ������ �缳��
		bMovingForward = !bMovingForward;

		// �̵� �Ÿ� ����
		NewLocation = CurrentLocation + Direction * MoveSpeed * DeltaTime;
	}

	// �� ��ġ ����
	SetActorLocation(NewLocation);
}

void AMyPlatform_M::MovePivotToCenter()
{
	if (!StaticMeshComp) return;

	// �޽��� ��� �ڽ��� ������
	FBox Bounds = StaticMeshComp->GetStaticMesh()->GetBounds().GetBox();

	// ��� �ڽ��� �߽� ���
	FVector Center = Bounds.GetCenter();

	// �ǹ� ��ġ�� �߾����� �̵�
	StaticMeshComp->SetRelativeLocation(-Center);
}

void AMyPlatform_M::SetRandomMoveSpeed()
{
	//�̵� �ӵ� ���������� ����(1000 ~ 3000 �Ҽ���X)
	MoveSpeed = FMath::RandRange(1000, 3000);
}



