// A game demo used as a submission__Author Yan Wei.


#include "DataAsset/StartUp/DataAsset_StartUpDataHero.h"
#include "AbilitySystem/IllusionAbilitySystemComponent.h"
#include "AbilitySystem/IllusionGameplayAbility.h"
#include "IllusionDebugHelper.h"

//bool FIllusionAbilitySet::IsValid() const
//{
//	return InputTag.IsValid() && AbilityToGrant;
//}

void UDataAsset_StartUpDataHero::GiveToAbilitySystemComponent(UIllusionAbilitySystemComponent* InIllusionASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InIllusionASCToGive, ApplyLevel);

	for(const FIllusionAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InIllusionASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InIllusionASCToGive->GiveAbility(AbilitySpec);
	}
}
