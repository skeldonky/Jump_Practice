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

	// 회전 를 나타내는 변수(초당 도(degrees) 단위)
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//액터 Rotation
	void RotateBoat(float DeltaTime);

	// 피벗 위치를 중앙으로 이동
	void MovePivotToCenter();

	UFUNCTION(CallInEditor, Category = "Movement")
	void SetRandomRotationSpeed();
};
