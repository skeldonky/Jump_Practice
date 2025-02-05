// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPlatfrom_T.generated.h"

UCLASS()
class JUMP_PRACTICE_API AMyPlatfrom_T : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPlatfrom_T();

protected:

	//Scene, StaticMeshComp
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, Category = "Timer")
	float FDisppearTime = 5.0f; // 최조 사라지는 시간 (초 단위)
	UPROPERTY(EditAnywhere, Category = "Timer")
	float AppearTime = 5.0f; // 나타나는 시간 (초 단위)
	UPROPERTY(EditAnywhere, Category = "Timer")
	float DisappearTime = 5.0f; // 사라지는 시간 (초 단위)

	FTimerHandle AppearTimerHandle;
	FTimerHandle DisappearTimerHandle;

	void Appear();
	void Disappear();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
