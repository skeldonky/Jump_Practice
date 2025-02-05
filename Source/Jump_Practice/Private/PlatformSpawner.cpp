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
	//게임 시작시 플랫폼 랜덤 스폰
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
	TArray<FVector> SpawnedLocations; // 이미 배치된 발판 위치 저장

	for (int32 i = 0; i < NumPlatforms; i++)
	{
		FVector SpawnLocation;
		bool bValidLocation = false;
		int32 MaxAttempts = 10; // 무한 루프 방지 (최대 10번 시도)
		int32 Attempts = 0;

		// 랜덤한 발판 클래스 선택
		UClass* PlatformClass = GetRandomPlatformClass();
		if (!PlatformClass) continue;

		//이동발판이면
		if (PlatformClass == AMyPlatform_M::StaticClass())
		{
			//거리 5배 늘려주기
			MinDistanceBetweenPlatforms = MinDistanceBetweenPlatforms * 5;
		}

		while (!bValidLocation && Attempts < MaxAttempts)
		{
			// 랜덤한 위치 생성
			SpawnLocation = SpawnerLocation + FVector(
				FMath::RandRange(-SpawnRange.X, SpawnRange.X),
				FMath::RandRange(-SpawnRange.Y, SpawnRange.Y),
				FMath::RandRange(0.0, SpawnRange.Z)
			);

			// 기존 배치된 위치와 거리 확인
			bValidLocation = true; // 기본적으로 유효한 위치로 설정
			for (const FVector& ExistingLocation : SpawnedLocations)
			{
				// 최소 거리 유지
				if (FVector::Dist(SpawnLocation, ExistingLocation) < MinDistanceBetweenPlatforms)
				{
					bValidLocation = false;
					break;
				}
			}

			Attempts++; // 시도 횟수 증가
		}

		//위치 정해지고 이동발판이면(음 맘에드는 방법은 아닌거같음)
		if (PlatformClass == AMyPlatform_M::StaticClass())
		{
			//거리 원상 복구 늘려주기
			MinDistanceBetweenPlatforms = MinDistanceBetweenPlatforms / 5;
		}

		// 유효한 위치를 찾았다면 스폰
		if (bValidLocation)
		{
			FRotator SpawnRotation = FRotator(0.f, FMath::RandRange(0.f, 360.f), 0.f);
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// 발판 스폰
			AActor* SpawnedPlatform = GetWorld()->SpawnActor<AActor>(PlatformClass, SpawnLocation, SpawnRotation, SpawnParams);

			// 스폰된 발판 위치 저장
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

	// 랜덤으로 하나 선택
	int32 RandomIndex = FMath::RandRange(0, PlatformClasses.Num() - 1);
	return PlatformClasses[RandomIndex];
}

