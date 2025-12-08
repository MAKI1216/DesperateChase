// Fill out your copyright notice in the Description page of Project Settings.


#include "DesperateChase\Player\MyBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"

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
	
}

// Called every frame
void AMyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyBaseCharacter::Move(const FInputActionValue& Value)
{
}

void AMyBaseCharacter::Look(const FInputActionValue& Value)
{
}

// Called to bind functionality to input
void AMyBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

