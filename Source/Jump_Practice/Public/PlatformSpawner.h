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

	// ������ ���� ����
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int32 NumPlatforms = 10;

	// ������ ���� (�������� ��ġ�� �������� ����� ����)
	UPROPERTY(EditAnywhere, Category = "Spawning")
	FVector SpawnRange = FVector(3000.f, 3000.f, 100.f);

	// ���ǵ� �� �ּ� �Ÿ�
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float MinDistanceBetweenPlatforms = 200.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ���� ���� �Լ�
	void SpawnPlatforms();

	// �������� ���� Ŭ������ �����ϴ� �Լ�
	UClass* GetRandomPlatformClass();
};
