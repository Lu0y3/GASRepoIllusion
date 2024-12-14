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

	//��ɫ�ƶ��ٶ�
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	//��Ҫ���ݽ�ɫ�ƶ�����ٶ������˶�״̬
	if (GroundSpeed <= ToggleWalkRunSpeed)
	{
		GroundRunSpeed = 0.f; //���л���walkʱ Run�ٶ���0

		GroundWalkSpeed = GroundSpeed;
	}
	else if (GroundSpeed > ToggleWalkRunSpeed)
	{
		GroundWalkSpeed = 0.f;

		GroundRunSpeed = GroundSpeed;
	}
	//���Ŀǰ�ĵ�����ٶ�
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
