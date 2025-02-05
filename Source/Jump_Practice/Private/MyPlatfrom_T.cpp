// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlatfrom_T.h"

// Sets default values
AMyPlatfrom_T::AMyPlatfrom_T()
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
}

// 발판을 다시 보이게 하고 충돌을 활성화하는 함수
void AMyPlatfrom_T::Appear()
{
	//발판 보이게하고 충돌 활성화
	StaticMeshComp->SetVisibility(true);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// 일정 시간이 지난 후 Disappear() 함수 실행하여 다시 숨기도록 설정
	GetWorldTimerManager().SetTimer(DisappearTimerHandle, this, &AMyPlatfrom_T::Disappear, FDisppearTime, false);
}

// 발판을 숨기고 충돌을 비활성화하는 함수
void AMyPlatfrom_T::Disappear()
{
	//발판 안보이게하고 충돌 비활성화
	StaticMeshComp->SetVisibility(false);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 일정 시간이 지난 후 Appear() 함수 실행하여 다시 나타나도록 설정
	GetWorldTimerManager().SetTimer(DisappearTimerHandle, this, &AMyPlatfrom_T::Appear, DisappearTime, false);
}

// Called when the game starts or when spawned
void AMyPlatfrom_T::BeginPlay()
{
	Super::BeginPlay();
	
	// 일정 시간이 지난 후 Disappear() 함수 실행
	GetWorldTimerManager().SetTimer(AppearTimerHandle, this, &AMyPlatfrom_T::Disappear, AppearTime, false);
}

// Called every frame
void AMyPlatfrom_T::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

