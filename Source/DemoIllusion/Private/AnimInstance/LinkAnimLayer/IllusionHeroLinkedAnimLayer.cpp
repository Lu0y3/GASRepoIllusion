// A game demo used as a submission__Author Yan Wei.


#include "AnimInstance/LinkAnimLayer/IllusionHeroLinkedAnimLayer.h"
#include "AnimInstance/IllusionHeroAnimInstance.h"

UIllusionHeroAnimInstance* UIllusionHeroLinkedAnimLayer::GetIllusionHeroAnimInstance() const
{
	return Cast<UIllusionHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
