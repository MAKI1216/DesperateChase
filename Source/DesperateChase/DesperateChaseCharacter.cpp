// Copyright Epic Games, Inc. All Rights Reserved.

// 包含头文件
#include "DesperateChaseCharacter.h"
#include "DesperateChaseProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"


//////////////////////////////////////////////////////////////////////////
// ADesperateChaseCharacter 实现

/**
 * 构造函数：初始化角色的基本属性和组件
 */
ADesperateChaseCharacter::ADesperateChaseCharacter()
{
	// 初始状态下角色没有步枪
	bHasRifle = false;
	
	// 设置碰撞胶囊的大小（半径，高度）
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// 创建第一人称相机组件	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent()); // 附加到胶囊组件
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // 设置相机位置
	FirstPersonCameraComponent->bUsePawnControlRotation = true; // 相机随角色控制旋转

	// 创建第一人称视角的骨骼网格组件
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true); // 只有所有者可以看到此网格
	Mesh1P->SetupAttachment(FirstPersonCameraComponent); // 附加到相机组件
	Mesh1P->bCastDynamicShadow = false; // 不投射动态阴影
	Mesh1P->CastShadow = false; // 不投射阴影
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f)); // 可选的旋转设置（已注释）
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f)); // 设置相对位置

}

/**
 * 游戏开始时调用的初始化方法
 */
void ADesperateChaseCharacter::BeginPlay()
{
	// 调用父类的BeginPlay方法  
	Super::BeginPlay();

	// 添加输入映射上下文，启用输入系统
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// 输入处理

/**
 * 设置玩家输入组件，绑定输入动作
 * @param PlayerInputComponent 玩家输入组件
 */
void ADesperateChaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// 设置动作绑定
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 跳跃动作绑定：按下时跳跃，释放时停止跳跃
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// 移动动作绑定：触发时调用Move方法
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADesperateChaseCharacter::Move);

		// 视角旋转动作绑定：触发时调用Look方法
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADesperateChaseCharacter::Look);
	}
}


/**
 * 处理移动输入的方法
 * @param Value 输入动作值（包含2D向量）
 */
void ADesperateChaseCharacter::Move(const FInputActionValue& Value)
{
	// 获取输入的2D向量
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 添加前后移动（Y轴）
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		// 添加左右移动（X轴）
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

/**
 * 处理视角旋转输入的方法
 * @param Value 输入动作值（包含2D向量）
 */
void ADesperateChaseCharacter::Look(const FInputActionValue& Value)
{
	// 获取输入的2D向量
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 添加偏航旋转（X轴：左右移动鼠标）
		AddControllerYawInput(LookAxisVector.X);
		// 添加俯仰旋转（Y轴：上下移动鼠标）
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

/**
 * 设置角色是否拥有步枪的方法
 * @param bNewHasRifle 新的步枪状态
 */
void ADesperateChaseCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

/**
 * 获取角色是否拥有步枪的方法
 * @return 角色当前是否拥有步枪
 */
bool ADesperateChaseCharacter::GetHasRifle()
{
	return bHasRifle;
}