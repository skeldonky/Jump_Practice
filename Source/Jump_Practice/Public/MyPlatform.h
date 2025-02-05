// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPlatform.generated.h"

UCLASS()
class JUMP_PRACTICE_API AMyPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPlatform();

protected:
	//Scene, StaticMeshComp
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	// ȸ�� �� ��Ÿ���� ����(�ʴ� ��(degrees) ����)
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//���� Rotation
	void RotateBoat(float DeltaTime);

	// �ǹ� ��ġ�� �߾����� �̵�
	void MovePivotToCenter();

	UFUNCTION(CallInEditor, Category = "Movement")
	void SetRandomRotationSpeed();
};
