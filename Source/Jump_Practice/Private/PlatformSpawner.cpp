// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformSpawner.h"
#include "MyPlatfrom_T.h"
#include "MyPlatform_M.h"
#include "MyPlatform.h"

// Sets default values
APlatformSpawner::APlatformSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();
	//���� ���۽� �÷��� ���� ����
	SpawnPlatforms();
}

// Called every frame
void APlatformSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformSpawner::SpawnPlatforms()
{
	if (!GetWorld()) return;

	FVector SpawnerLocation = GetActorLocation();
	TArray<FVector> SpawnedLocations; // �̹� ��ġ�� ���� ��ġ ����

	for (int32 i = 0; i < NumPlatforms; i++)
	{
		FVector SpawnLocation;
		bool bValidLocation = false;
		int32 MaxAttempts = 10; // ���� ���� ���� (�ִ� 10�� �õ�)
		int32 Attempts = 0;

		// ������ ���� Ŭ���� ����
		UClass* PlatformClass = GetRandomPlatformClass();
		if (!PlatformClass) continue;

		//�̵������̸�
		if (PlatformClass == AMyPlatform_M::StaticClass())
		{
			//�Ÿ� 5�� �÷��ֱ�
			MinDistanceBetweenPlatforms = MinDistanceBetweenPlatforms * 5;
		}

		while (!bValidLocation && Attempts < MaxAttempts)
		{
			// ������ ��ġ ����
			SpawnLocation = SpawnerLocation + FVector(
				FMath::RandRange(-SpawnRange.X, SpawnRange.X),
				FMath::RandRange(-SpawnRange.Y, SpawnRange.Y),
				FMath::RandRange(0.0, SpawnRange.Z)
			);

			// ���� ��ġ�� ��ġ�� �Ÿ� Ȯ��
			bValidLocation = true; // �⺻������ ��ȿ�� ��ġ�� ����
			for (const FVector& ExistingLocation : SpawnedLocations)
			{
				// �ּ� �Ÿ� ����
				if (FVector::Dist(SpawnLocation, ExistingLocation) < MinDistanceBetweenPlatforms)
				{
					bValidLocation = false;
					break;
				}
			}

			Attempts++; // �õ� Ƚ�� ����
		}

		//��ġ �������� �̵������̸�(�� ������� ����� �ƴѰŰ���)
		if (PlatformClass == AMyPlatform_M::StaticClass())
		{
			//�Ÿ� ���� ���� �÷��ֱ�
			MinDistanceBetweenPlatforms = MinDistanceBetweenPlatforms / 5;
		}

		// ��ȿ�� ��ġ�� ã�Ҵٸ� ����
		if (bValidLocation)
		{
			FRotator SpawnRotation = FRotator(0.f, FMath::RandRange(0.f, 360.f), 0.f);
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// ���� ����
			AActor* SpawnedPlatform = GetWorld()->SpawnActor<AActor>(PlatformClass, SpawnLocation, SpawnRotation, SpawnParams);

			// ������ ���� ��ġ ����
			if (SpawnedPlatform)
			{
				SpawnedLocations.Add(SpawnLocation);
			}
		}
	}
}

UClass* APlatformSpawner::GetRandomPlatformClass()
{
	TArray<UClass*> PlatformClasses = {
		AMyPlatform::StaticClass(),
		AMyPlatform_M::StaticClass(),
		AMyPlatfrom_T::StaticClass()
	};

	// �������� �ϳ� ����
	int32 RandomIndex = FMath::RandRange(0, PlatformClasses.Num() - 1);
	return PlatformClasses[RandomIndex];
}

