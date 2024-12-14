// A game demo used as a submission__Author Yan Wei.


#include "DataAsset/StartUp/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/IllusionAbilitySystemComponent.h"
#include "AbilitySystem/IllusionGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UIllusionAbilitySystemComponent* InIllusionASCToGive, int32 ApplyLevel)
{
	check(InIllusionASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InIllusionASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InIllusionASCToGive, ApplyLevel);


	if (!StartUpGameplayEffect.IsEmpty())
	{
		for (const  TSubclassOf <  UGameplayEffect >& EffectClass : StartUpGameplayEffect)
		{
			if (!EffectClass)
			{
				continue;
			}

			//ASC����GameplayEffect
			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
			InIllusionASCToGive->ApplyGameplayEffectToSelf(
				EffectCDO,
				ApplyLevel,
				InIllusionASCToGive->MakeEffectContext()
			);
		}
	}

}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UIllusionGameplayAbility>>& InAbilitiesToGive, UIllusionAbilitySystemComponent* InIllusionASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}
	for (const TSubclassOf<UIllusionGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability)
		{
			continue;
		}

		FGameplayAbilitySpec Spec(Ability);  //�����˽�Spec���ܵĲ�������
		Spec.SourceObject = InIllusionASCToGive->GetAvatarActor(); //Object this ability was created from ACS������ӵ����
		Spec.Level = ApplyLevel;

		//����ASC����Ȼ�����OnGiveAbility
		InIllusionASCToGive->GiveAbility(Spec);
	}

}
