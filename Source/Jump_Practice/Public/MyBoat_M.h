// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBoat_M.generated.h"

UCLASS()
class JUMP_PRACTICE_API AMyBoat_M : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBoat_M();

protected:
	//Scene, StaticMeshComp
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	//�̵��ӵ�, �ִ� �̵��Ÿ� ����
	FVector BaseLocation;

	// ���� �̵� �ӵ�
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 200.0f;

	// �ִ� �̵� �Ÿ�
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxRange = 2000.0f;

	// ���� �̵� ����
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector Direction = FVector(1.0f, 1.0f, 0.0f); // �밢�� �⺻ ����

	// ���� ��ġ ����
	FVector StartLocation;

	// ���� �̵� ������ ���������� ���� (�պ� ó����)
	bool bMovingForward = true;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//�̵� �Լ�
	void MovePlatform(float DeltaTime);
};
