// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlatfrom_T.h"

// Sets default values
AMyPlatfrom_T::AMyPlatfrom_T()
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
}

// ������ �ٽ� ���̰� �ϰ� �浹�� Ȱ��ȭ�ϴ� �Լ�
void AMyPlatfrom_T::Appear()
{
	//���� ���̰��ϰ� �浹 Ȱ��ȭ
	StaticMeshComp->SetVisibility(true);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// ���� �ð��� ���� �� Disappear() �Լ� �����Ͽ� �ٽ� ���⵵�� ����
	GetWorldTimerManager().SetTimer(DisappearTimerHandle, this, &AMyPlatfrom_T::Disappear, FDisppearTime, false);
}

// ������ ����� �浹�� ��Ȱ��ȭ�ϴ� �Լ�
void AMyPlatfrom_T::Disappear()
{
	//���� �Ⱥ��̰��ϰ� �浹 ��Ȱ��ȭ
	StaticMeshComp->SetVisibility(false);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// ���� �ð��� ���� �� Appear() �Լ� �����Ͽ� �ٽ� ��Ÿ������ ����
	GetWorldTimerManager().SetTimer(DisappearTimerHandle, this, &AMyPlatfrom_T::Appear, DisappearTime, false);
}

// Called when the game starts or when spawned
void AMyPlatfrom_T::BeginPlay()
{
	Super::BeginPlay();
	
	// ���� �ð��� ���� �� Disappear() �Լ� ����
	GetWorldTimerManager().SetTimer(AppearTimerHandle, this, &AMyPlatfrom_T::Disappear, AppearTime, false);
}

// Called every frame
void AMyPlatfrom_T::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

