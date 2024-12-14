// A game demo used as a submission__Author Yan Wei.


#include "DataAsset/StartUp/DataAsset_StartUpDataEnemy.h"
#include "AbilitySystem/IllusionAbilitySystemComponent.h"
#include "AbilitySystem/GA/IllusionGameplayAbilityEnemy.h"

void UDataAsset_StartUpDataEnemy::GiveToAbilitySystemComponent(UIllusionAbilitySystemComponent* InIllusionASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InIllusionASCToGive, ApplyLevel);

	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf<UIllusionGameplayAbilityEnemy>& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass)
			{
				continue;
			}

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InIllusionASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;

			InIllusionASCToGive->GiveAbility(AbilitySpec);
		}
	}

}
