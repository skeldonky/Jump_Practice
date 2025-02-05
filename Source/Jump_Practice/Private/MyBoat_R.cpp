// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBoat_R.h"

// 생성자
AMyBoat_R::AMyBoat_R()
{
	// Tick을 활성화해, 매 프레임 Tick 함수가 호출되도록 설정
	PrimaryActorTick.bCanEverTick = true;

	// Component들
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

	// 기본 회전 속도
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

//보트 회전
void AMyBoat_R::RotateBoat(float DeltaTime)
{
	// RotationSpeed가 0이 아니라면 회전 처리
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		// 초당 RotationSpeed만큼, 한 프레임당 (RotationSpeed * DeltaTime)만큼 회전
		AddActorLocalRotation(FRotator(RotationSpeed * DeltaTime, 0.0f, 0.0f));
	}
}

