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
	// 생성자
	AMyBoat_R();

protected:
	
	// 루트 컴포넌트를 나타내는 Scene Component 포인터 Static Mesh Component 포인터
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	// 회전 를 나타내는 변수(초당 도(degrees) 단위)
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//액터 Rotation
	void RotateBoat(float DeltaTime);

};
