// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBoat_M.h"

// Sets default values
AMyBoat_M::AMyBoat_M()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Component들
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

	//여기해야 0, 0, 0 이 아니다(생성자에 넣으면 0, 0, 0)
	StartLocation = GetActorLocation();

	// 방향 벡터 (속도 계산 시 사용)
	Direction = Direction.GetSafeNormal();
}

// Called every frame
void AMyBoat_M::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
}

//발판 이동
void AMyBoat_M::MovePlatform(float DeltaTime)
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

