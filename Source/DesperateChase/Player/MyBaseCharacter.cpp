// Fill out your copyright notice in the Description page of Project Settings.


#include "DesperateChase\Player\MyBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AMyBaseCharacter::AMyBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//相机设置
	FPCamera= CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	if(FPCamera)
	{
		FPCamera->SetupAttachment(RootComponent);
		FPCamera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // 设置相机位置
		FPCamera->bUsePawnControlRotation = true; // 相机随角色控制旋转
	}

	//设置第一人称网格
	FPArmMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPArmMesh"));
	if(FPArmMesh)
	{
		FPArmMesh->SetupAttachment(FPCamera);
		FPArmMesh->SetOnlyOwnerSee(true); // 只有所有者可以看到此网格
		FPArmMesh->bCastDynamicShadow = false; // 不投射动态阴影
		FPArmMesh->CastShadow = false; // 不投射阴影
		FPArmMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f)); // 设置相对位置
	}

	//设置第一人称网格
	FPArmMesh2=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPArmMesh2"));
	if(FPArmMesh2)
	{
		FPArmMesh2->SetupAttachment(FPCamera);
		FPArmMesh2->SetOnlyOwnerSee(true); // 只有所有者可以看到此网格
		FPArmMesh2->bCastDynamicShadow = false; // 不投射动态阴影
		FPArmMesh2->CastShadow = false; // 不投射阴影
		FPArmMesh2->SetRelativeLocation(FVector(-30.f, 0.f, -150.f)); // 设置相对位置
	}
	//设置第三人称网格
	TPMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TPMesh"));
	if(TPMesh)
	{
		TPMesh->SetOwnerNoSee(true);
		TPMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//仅仅用于射线检测，物理世界碰撞用的是胶囊
		TPMesh->SetCollisionObjectType(ECC_Pawn);
	}
}

// Called when the game starts or when spawned
void AMyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void AMyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyBaseCharacter::Move(const FInputActionValue& Value)
{
	// 输入是一个二维向量
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 添加移动输入
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMyBaseCharacter::Look(const FInputActionValue& Value)
{
	// 输入是一个二维向量
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 添加控制器旋转输入（偏航和俯仰）
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

// Called to bind functionality to input
void AMyBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 设置动作绑定
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 跳跃
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// 移动
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyBaseCharacter::Move);

		// 视角
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyBaseCharacter::Look);
	}
}

