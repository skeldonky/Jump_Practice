// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
//카메라, 스프링 암 실제구현이 필요한 경우라서 include해줘야함
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
//컨트롤 입력 참조
#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
//이동속도 관련 참조
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. 스프링 암 생성
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	// 스프링 암을 루트 컴포넌트(CapsuleComponent)에 부착
	SpringArmComp->SetupAttachment(RootComponent);
	// 캐릭터와 카메라 사이의 거리 기본값 300으로 설정
	SpringArmComp->TargetArmLength = 300.0f;
	//컨트롤러 회전에 따라 스프링 암도 회전하도록 설정
	SpringArmComp->bUsePawnControlRotation = true;

	// 2. 카메라 컴포넌트 생성
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// 스프링 암의 소켓 위치에 카메라를 부착
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	// 카메라는 스프링 암의 회전을 따르므로 PawnControlRotation은 꺼야한다.
	CameraComp->bUsePawnControlRotation = false;

	//이동속도들 기본값
	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.5f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;
	//이동속도 설정
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//점프 높이
	GetCharacterMovement()->JumpZVelocity = JumpHeight;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Enhanced inputComponent로 캐스팅
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//IA 를 가져오기 위해 현재 소유중인 Controller를 ASpartaPlayerController로 캐스팅
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				//IA_Move 액션 키를 누르고 있는 동안 Move() 호출
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
			}

			if (PlayerController->JumpAction)
			{
				//IA_Jump 액션 키를 누르고있는동안 StartJump() 호출
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::StartJump);

				//IA_Jump 액션 키를 때면은 StopJump() 호출
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJump);
			}

			if (PlayerController->LookAction)
			{
				//IA_Look 액션 마우스가 움직일때 Look() 호출
				EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
			}

			if (PlayerController->RunAction)
			{
				//IA_Sprint 액션 키를 누르고 있는 동안 StartSprint() 호출
				EnhancedInput->BindAction(PlayerController->RunAction, ETriggerEvent::Triggered, this, &AMyCharacter::StartRun);

				//IA_Sprint 액션 키를 때면은 StopSprint() 호출
				EnhancedInput->BindAction(PlayerController->RunAction, ETriggerEvent::Completed, this, &AMyCharacter::StopRun);
			}
		}
	}
}

void AMyCharacter::Move(const FInputActionValue& value)
{
	//컨트롤러가 있어야 방향 계산이 가능
	if (!Controller)
	{
		return;
	}

	//Value는 Axis2D로 설정된 IA_Move의 입력값 (WASD)을 담고 있음
	// 예) (X=1,Y=0) -> 전진 / (X=-1, Y=0) → 후진 / (X=0, Y=1) → 오른쪽 / (X=0, Y=-1) → 왼쪽
	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		//캐릭터가 바라보는 방향(정면)으로 X축 이동
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		//캐릭터가 바라보는 방향(정면)으로 X축 이동
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void AMyCharacter::StartJump(const FInputActionValue& value)
{
	// Jump 함수는 Character가 기본 제공
	if (value.Get<bool>())
	{
		Jump();
	}
}

void AMyCharacter::StopJump(const FInputActionValue& value)
{
	// StopJumping 함수도 Character가 기본 제공
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}

void AMyCharacter::Look(const FInputActionValue& value)
{
	//마우스의 X, Y 움직임을 2D 축으로 가져옴
	FVector2D LookInput = value.Get<FVector2D>();

	// X는 좌우 회전(Yaw), Y는 상하 회전 (Pitch)
	//좌우 회전
	AddControllerYawInput(LookInput.X);
	//상하 회전
	AddControllerPitchInput(LookInput.Y);
}

void AMyCharacter::StartRun(const FInputActionValue& value)
{
	// Shift 키를 누른 순간 이 함수가 호출된다고 가정
	// 스프린트 속도를 적용
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void AMyCharacter::StopRun(const FInputActionValue& value)
{
	// Shift 키를 때는 순간 이 함수가 호출
	// 평상시 속도로 복귀
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}

