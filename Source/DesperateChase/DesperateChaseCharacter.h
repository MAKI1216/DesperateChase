// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// 包含必要的头文件
#include "CoreMinimal.h"                   // UE核心最小头文件
#include "GameFramework/Character.h"       // 角色基类头文件
#include "InputActionValue.h"              // 输入动作值头文件
#include "DesperateChaseCharacter.generated.h"  // 自动生成的反射头文件

// 前向声明，减少编译依赖
class UInputComponent;                     // 输入组件类
class USkeletalMeshComponent;              // 骨骼网格组件类
class USceneComponent;                     // 场景组件类
class UCameraComponent;                    // 相机组件类
class UAnimMontage;                        // 动画蒙太奇类
class USoundBase;                          // 声音基类

/**
 * ADesperateChaseCharacter类是游戏中的玩家角色类
 * 继承自ACharacter，实现了第一人称视角的角色控制和功能
 */
UCLASS(config=Game)                         // 标记为UE可配置类
class ADesperateChaseCharacter : public ACharacter
{
	GENERATED_BODY()                       // 自动生成的反射代码宏

private:
	/** 第一人称视角的骨骼网格组件（玩家看到的自己的手臂） */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** 第一人称相机组件，控制玩家的视角 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** 输入映射上下文，定义输入按键与动作的关联 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** 跳跃动作输入，绑定跳跃按键 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** 移动动作输入，绑定方向键或WASD */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

public:
	/** 默认构造函数 */
	ADesperateChaseCharacter();

protected:
	/** 游戏开始时调用的初始化方法 */
	virtual void BeginPlay() override;

public:		
	/** 视角旋转动作输入，绑定鼠标移动 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** 布尔值，用于动画蓝图切换不同的动画集（是否持有步枪） */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** 设置是否拥有步枪的方法（蓝图可调用） */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** 获取是否拥有步枪的方法（蓝图可调用） */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	/** 处理移动输入的方法 */
	void Move(const FInputActionValue& Value);

	/** 处理视角旋转输入的方法 */
	void Look(const FInputActionValue& Value);

protected:
	// APawn接口重写
	/** 设置玩家输入组件的方法，绑定输入动作 */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** 获取第一人称网格组件的方法 */
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** 获取第一人称相机组件的方法 */
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

