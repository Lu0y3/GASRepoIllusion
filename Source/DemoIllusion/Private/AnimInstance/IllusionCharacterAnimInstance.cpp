// A game demo used as a submission__Author Yan Wei.


#include "AnimInstance/IllusionCharacterAnimInstance.h"
#include "Characters/IllusionCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UIllusionCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AIllusionCharacterBase>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UIllusionCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent) return;

	//角色移动速度
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	//需要根据角色移动最大速度来调运动状态
	if (GroundSpeed <= ToggleWalkRunSpeed)
	{
		GroundRunSpeed = 0.f; //当切换到walk时 Run速度至0

		GroundWalkSpeed = GroundSpeed;
	}
	else if (GroundSpeed > ToggleWalkRunSpeed)
	{
		GroundWalkSpeed = 0.f;

		GroundRunSpeed = GroundSpeed;
	}
	//获得目前的地面加速度
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
