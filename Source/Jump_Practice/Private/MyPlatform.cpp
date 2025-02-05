// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlatform.h"

// Sets default values
AMyPlatform::AMyPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Component들
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

	// 기본 회전 속도
	RotationSpeed = 90.0f;
}

// Called when the game starts or when spawned
void AMyPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	// 피벗을 중앙으로 이동(발판 중앙좌표 기준으로 움직이게 하기 위해서)
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
	// RotationSpeed가 0이 아니라면 회전 처리
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		// 초당 RotationSpeed만큼, 한 프레임당 (RotationSpeed * DeltaTime)만큼 회전
		AddActorLocalRotation(FRotator(0.0f, 0.0f, RotationSpeed * DeltaTime));
	}
}

void AMyPlatform::MovePivotToCenter()
{
	if (!StaticMeshComp) return;

	// 메시의 경계 박스를 가져옴
	FBox Bounds = StaticMeshComp->GetStaticMesh()->GetBounds().GetBox();

	// 경계 박스의 중심 계산
	FVector Center = Bounds.GetCenter();

	// 피벗 위치를 중앙으로 이동
	StaticMeshComp->SetRelativeLocation(-Center);
}

void AMyPlatform::SetRandomRotationSpeed()
{
	//회전 속도 랜덤값으로 설정(10 ~ 180 소수점X)
	RotationSpeed = FMath::RandRange(10, 180);
}

