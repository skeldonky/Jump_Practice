// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBoat_M.h"

// Sets default values
AMyBoat_M::AMyBoat_M()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Component��
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	//Mesh, Material
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Cabin_Lake/Meshes/Boat/SM_Boat_02.SM_Boat_02"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Cabin_Lake/Materials/MI_boat.MI_boat"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	BaseLocation = FVector(0, MoveSpeed, 0);
}

// Called when the game starts or when spawned
void AMyBoat_M::BeginPlay()
{
	Super::BeginPlay();

	//�����ؾ� 0, 0, 0 �� �ƴϴ�(�����ڿ� ������ 0, 0, 0)
	StartLocation = GetActorLocation();

	// ���� ���� (�ӵ� ��� �� ���)
	Direction = Direction.GetSafeNormal();
}

// Called every frame
void AMyBoat_M::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
}

//���� �̵�
void AMyBoat_M::MovePlatform(float DeltaTime)
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

