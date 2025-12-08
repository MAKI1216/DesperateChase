// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyBaseCharacter.generated.h"

// 前向声明，减少编译依赖
struct FInputActionValue;
class UAnimInstance;
class UInputComponent;                     // 输入组件类
class USkeletalMeshComponent;              // 骨骼网格组件类
class USceneComponent;                     // 场景组件类
class UCameraComponent;                    // 相机组件类
class UAnimMontage;                        // 动画蒙太奇类
class USoundBase;                          // 声音基类

UCLASS()
class DESPERATECHASE_API AMyBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyBaseCharacter();

private:
#pragma region Character Components
	/** 第一人称相机组件，控制玩家的视角 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FPCamera;

	/** 第一人称手臂骨骼网格组件，用于显示武器等物品 */
	UPROPERTY(Category=Character,VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* FPArmMesh;

	/** 手臂附件骨骼网格体 */
	UPROPERTY(Category=Character,VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* FPArmMesh2;

	/** 第三人称骨骼网格组件，用于显示角色模型 */
	UPROPERTY(Category=Character,VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* TPMesh;

	UPROPERTY(Category=Character,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	UAnimInstance* ClientArmsAnimBP;//手臂动画蓝图

	UPROPERTY(Category=Character,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	UAnimInstance* ServerBodysAnimBP;//身体动画蓝图
	
#pragma endregion Character Components

public:
#pragma region Character Input
/** 输入映射上下文，定义输入按键与动作的关联 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** 跳跃动作输入，绑定跳跃按键 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** 移动动作输入，绑定方向键或WASD */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** 视角旋转动作输入，绑定鼠标移动 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** 处理移动输入的方法 */
	void Move(const FInputActionValue& Value);

	/** 处理视角旋转输入的方法 */
	void Look(const FInputActionValue& Value);
#pragma endregion Character Input

protected:
	// APawn接口重写
	/** 设置玩家输入组件的方法，绑定输入动作 */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
