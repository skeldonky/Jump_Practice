// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPlatform_M.generated.h"

UCLASS()
class JUMP_PRACTICE_API AMyPlatform_M : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPlatform_M();

protected:

	//Scene, StaticMeshComp
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	//이동속도, 최대 이동거리 변수
	FVector BaseLocation;

	// 발판 이동 속도
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 2000.0f;

	// 최대 이동 거리
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxRange = 2000.0f;

	// 현재 이동 방향
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector Direction = FVector(1.0f, 1.0f, 0.0f); // 대각선 기본 방향

	// 시작 위치 저장
	FVector StartLocation;

	// 현재 이동 방향이 정방향인지 여부 (왕복 처리용)
	bool bMovingForward = true;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//이동 함수
	void MovePlatform(float DeltaTime);

	// 피벗 위치를 중앙으로 이동
	void MovePivotToCenter();

	//랜덤 버튼
	UFUNCTION(CallInEditor, Category = "Movement")
	void SetRandomMoveSpeed();
};
