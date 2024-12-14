// A game demo used as a submission__Author Yan Wei.


#include "AnimInstance/IllusionHeroAnimInstance.h"
#include "Characters/IllusionHeroCharacterBase.h"

void UIllusionHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (OwningCharacter)
	{
		OwningCharacterHeroBase = Cast<AIllusionHeroCharacterBase>(OwningCharacter);
	}
}

void UIllusionHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		EnterIdledTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		EnterIdledTime += DeltaSeconds;
		bShouldEnterRelaxState = (EnterIdledTime >= EnterRelaxStateTime);
	}

}
