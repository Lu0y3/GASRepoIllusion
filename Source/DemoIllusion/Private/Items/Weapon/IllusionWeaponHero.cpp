// A game demo used as a submission__Author Yan Wei.


#include "Items/Weapon/IllusionWeaponHero.h"

void AIllusionWeaponHero::AssginGrantedAbilitySpecHandle(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	//������ܵ�Spec Handles
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AIllusionWeaponHero::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
