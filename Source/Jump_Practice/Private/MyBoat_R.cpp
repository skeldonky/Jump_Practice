// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBoat_R.h"

// ������
AMyBoat_R::AMyBoat_R()
{
	// Tick�� Ȱ��ȭ��, �� ������ Tick �Լ��� ȣ��ǵ��� ����
	PrimaryActorTick.bCanEverTick = true;

	// Component��
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	// Mesh, Material
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

	// �⺻ ȸ�� �ӵ�
	RotationSpeed = 90.0f;
}

// Called when the game starts or when spawned
void AMyBoat_R::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBoat_R::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateBoat(DeltaTime);
}

//��Ʈ ȸ��
void AMyBoat_R::RotateBoat(float DeltaTime)
{
	// RotationSpeed�� 0�� �ƴ϶�� ȸ�� ó��
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		// �ʴ� RotationSpeed��ŭ, �� �����Ӵ� (RotationSpeed * DeltaTime)��ŭ ȸ��
		AddActorLocalRotation(FRotator(RotationSpeed * DeltaTime, 0.0f, 0.0f));
	}
}

