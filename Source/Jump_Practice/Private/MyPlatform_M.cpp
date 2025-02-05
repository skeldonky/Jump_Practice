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

	// 피벗을 먼저 중앙으로 이동
	MovePivotToCenter();
	
	//여기해야 0, 0, 0 이 아니다(생성자에 넣으면 0, 0, 0)
	StartLocation = GetActorLocation();

	// 방향 벡터 (속도 계산 시 사용)
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
	// 현재 위치 가져오기
	FVector CurrentLocation = GetActorLocation();

	// 이동 거리 계산
	FVector NewLocation = CurrentLocation + Direction * MoveSpeed * DeltaTime;

	// 시작 위치로부터의 이동 거리 계산
	float TraveledDistance = FVector::Dist(StartLocation, NewLocation);

	// 최대 거리 초과 시 방향 반전
	if (TraveledDistance >= MaxRange || TraveledDistance <= 0.0f)
	{
		// 방향 반전
		Direction *= -1;

		// 왕복을 위해 이동 방향을 재설정
		bMovingForward = !bMovingForward;

		// 이동 거리 제한
		NewLocation = CurrentLocation + Direction * MoveSpeed * DeltaTime;
	}

	// 새 위치 설정
	SetActorLocation(NewLocation);
}

void AMyPlatform_M::MovePivotToCenter()
{
	if (!StaticMeshComp) return;

	// 메시의 경계 박스를 가져옴
	FBox Bounds = StaticMeshComp->GetStaticMesh()->GetBounds().GetBox();

	// 경계 박스의 중심 계산
	FVector Center = Bounds.GetCenter();

	// 피벗 위치를 중앙으로 이동
	StaticMeshComp->SetRelativeLocation(-Center);
}

void AMyPlatform_M::SetRandomMoveSpeed()
{
	//이동 속도 랜덤값으로 설정(1000 ~ 3000 소수점X)
	MoveSpeed = FMath::RandRange(1000, 3000);
}



