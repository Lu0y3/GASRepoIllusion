// A game demo used as a submission__Author Yan Wei.


#include "AbilitySystem/IllusionAbilitySystemComponent.h"
#include "AbilitySystem/IllusionGameplayAbility.h"

#include "IllusionDebugHelper.h"

void UIllusionAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities()) //遍历ASC中的所有可激活的能力
	{
		//动态标签
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))  //精准匹配该标签
		{
			continue;
		}
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UIllusionAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
}

void UIllusionAbilitySystemComponent::GrantHeroWeaponAbilitiesToASC(const TArray<FIllusionAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel,
	TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}

	for (const FIllusionAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec Spec(AbilitySet.AbilityToGrant);
		Spec.SourceObject = this->GetAvatarActor();
		Spec.Level = ApplyLevel;
		Spec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		/*this->GiveAbility(Spec);*/ //直接激活

		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(Spec));//储存这个能力SpecHandle

	}
}

void UIllusionAbilitySystemComponent::RemovedGrantedHeroWeaponAbilitiesFromASC(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			this->ClearAbility(SpecHandle);
		}
	}

	InSpecHandlesToRemove.Empty();
}


