// A game demo used as a submission__Author Yan Wei.


#include "Characters/IllusionHeroCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IllusionGameplayTag.h"
#include "Component/Input/IllusionHeroInputComponent.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/StartUp/DataAsset_StartUpDataHero.h"
#include "Component/Combat/HeroCombatComponent.h"
#include "AbilitySystem/IllusionAbilitySystemComponent.h"

#include "IllusionDebugHelper.h"

AIllusionHeroCharacterBase::AIllusionHeroCharacterBase()
{

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraSpringArm->SetupAttachment(GetRootComponent());
	CameraSpringArm->TargetArmLength = 250.f;
	CameraSpringArm->SocketOffset = FVector(0.f, 50.f, 100.f);
	CameraSpringArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 750.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1500.f;
	

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>("HeroCombatComponent");
}

UPawnCombatComponent* AIllusionHeroCharacterBase::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

void AIllusionHeroCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!StartUpDataAsset.IsNull())
	{
		//ͬ������HeroDataAsset  ���Ҹ���ASC      LoadData��ӵ��IllusionGA
		if (UDataAsset_StartUpDataBase* LoadData = StartUpDataAsset.LoadSynchronous())
		{
			LoadData->GiveToAbilitySystemComponent(IllusionAbilitySystemComponent);
		}
	}
}

void AIllusionHeroCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AIllusionHeroCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("�������ʲ�ʧЧ"));
	//�����ǿ������ϵͳ
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* system = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(system);
	//����ǿ������ϵͳ������Mapping������
	system->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	//�õ���Ч�������
	UIllusionHeroInputComponent* HeroInputComponent = CastChecked<UIllusionHeroInputComponent>(PlayerInputComponent);
	//��Move Look
	HeroInputComponent->BindNativeInputAction(InputConfigDataAsset, IllusionGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AIllusionHeroCharacterBase::Input_Move);
	HeroInputComponent->BindNativeInputAction(InputConfigDataAsset, IllusionGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AIllusionHeroCharacterBase::Input_Look);
	HeroInputComponent->BindNativeInputAction(InputConfigDataAsset, IllusionGameplayTags::InputTag_Look_Zoom, ETriggerEvent::Triggered, this, &AIllusionHeroCharacterBase::Input_Look_Zoom);


	HeroInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AIllusionHeroCharacterBase::Input_AbilityInputPressed, &AIllusionHeroCharacterBase::Input_AbilityInputReleased);

	//IllusionDebug::Print(TEXT("_01 input binding"));
}

void AIllusionHeroCharacterBase::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	//�õ�����������ǰ��Ļ����Yawn
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		//Hero��ǰ�������ǿ�������Yaw��ǰ��   //��һ��Դ�룡����
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);

	}
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);

	}
}

void AIllusionHeroCharacterBase::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AIllusionHeroCharacterBase::Input_Look_Zoom(const FInputActionValue& InputActionValue)
{
	float MouseWheelValue = InputActionValue.Get<float>();
	//�ı�����۳���
	CameraSpringArm->TargetArmLength = FMath::Clamp(CameraSpringArm->TargetArmLength + MouseWheelValue*CameraLookZoomRatio, 180.f, 1000.f);
}

void AIllusionHeroCharacterBase::Input_AbilityInputPressed(FGameplayTag InputTag)
{
	IllusionAbilitySystemComponent->OnAbilityInputPressed(InputTag);
}

void AIllusionHeroCharacterBase::Input_AbilityInputReleased(FGameplayTag InputTag)
{
	IllusionAbilitySystemComponent->OnAbilityInputReleased(InputTag);

}
