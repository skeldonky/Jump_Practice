// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBoat_R.generated.h"

UCLASS()
class JUMP_PRACTICE_API AMyBoat_R : public AActor
{
	GENERATED_BODY()
	
public:	
	// ������
	AMyBoat_R();

protected:
	
	// ��Ʈ ������Ʈ�� ��Ÿ���� Scene Component ������ Static Mesh Component ������
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	// ȸ�� �� ��Ÿ���� ����(�ʴ� ��(degrees) ����)
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//���� Rotation
	void RotateBoat(float DeltaTime);

};
