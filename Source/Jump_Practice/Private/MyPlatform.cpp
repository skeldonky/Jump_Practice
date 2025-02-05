// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlatform.h"

// Sets default values
AMyPlatform::AMyPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Component��
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

	// �⺻ ȸ�� �ӵ�
	RotationSpeed = 90.0f;
}

// Called when the game starts or when spawned
void AMyPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	// �ǹ��� �߾����� �̵�(���� �߾���ǥ �������� �����̰� �ϱ� ���ؼ�)
	MovePivotToCenter();
}

// Called every frame
void AMyPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateBoat(DeltaTime);
}

void AMyPlatform::RotateBoat(float DeltaTime)
{
	// RotationSpeed�� 0�� �ƴ϶�� ȸ�� ó��
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		// �ʴ� RotationSpeed��ŭ, �� �����Ӵ� (RotationSpeed * DeltaTime)��ŭ ȸ��
		AddActorLocalRotation(FRotator(0.0f, 0.0f, RotationSpeed * DeltaTime));
	}
}

void AMyPlatform::MovePivotToCenter()
{
	if (!StaticMeshComp) return;

	// �޽��� ��� �ڽ��� ������
	FBox Bounds = StaticMeshComp->GetStaticMesh()->GetBounds().GetBox();

	// ��� �ڽ��� �߽� ���
	FVector Center = Bounds.GetCenter();

	// �ǹ� ��ġ�� �߾����� �̵�
	StaticMeshComp->SetRelativeLocation(-Center);
}

void AMyPlatform::SetRandomRotationSpeed()
{
	//ȸ�� �ӵ� ���������� ����(10 ~ 180 �Ҽ���X)
	RotationSpeed = FMath::RandRange(10, 180);
}

