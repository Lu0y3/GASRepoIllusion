// A game demo used as a submission__Author Yan Wei.


#include "StructTypes/IllusionStructTypes.h"
#include "AbilitySystem/IllusionGameplayAbility.h"


bool FIllusionInputActionConfig::IsValid() const
{
	return InputAction && InputTag.IsValid();
}


bool FIllusionAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}