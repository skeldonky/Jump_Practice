// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

UCLASS()
class JUMP_PRACTICE_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformSpawner();

protected:

	// 스폰할 발판 개수
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int32 NumPlatforms = 10;

	// 스폰할 범위 (스포너의 위치를 기준으로 상대적 범위)
	UPROPERTY(EditAnywhere, Category = "Spawning")
	FVector SpawnRange = FVector(3000.f, 3000.f, 100.f);

	// 발판들 간 최소 거리
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float MinDistanceBetweenPlatforms = 200.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 발판 스폰 함수
	void SpawnPlatforms();

	// 랜덤으로 발판 클래스를 선택하는 함수
	UClass* GetRandomPlatformClass();
};
