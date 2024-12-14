// A game demo used as a submission__Author Yan Wei.


#include "Component/Combat/HeroCombatComponent.h"
#include "Items/Weapon/IllusionWeaponHero.h"
#include "IllusionGameplayTag.h"
#include "IllusionDebugHelper.h"
#include "AbilitySystemBlueprintLibrary.h"

AIllusionWeaponHero* UHeroCombatComponent::GetHeroWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AIllusionWeaponHero>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AIllusionWeaponHero* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AIllusionWeaponHero>(GetCharacterCurrentCarriedWeapon());
	
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	//-Begin  �����������ഫ������OtherActor _Tarry
	if (OverlappedActors.Contains(HitActor))
	{
		//IllusionDebug::Print(TEXT("_005"));

		return;
	}
	/*��Ҫ��overlap������ʱ�����������õ�λ�����ڸ���Ľ�������λ�����*/
	OverlappedActors.AddUnique(HitActor);
	IllusionDebug::Print(TEXT("Hero Combat OverlapTarget!"));

	//-End

	//-Begin �����¼���ǩ��Actor��������Hero��ͼ��֪�������HitActor
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		IllusionGameplayTags::Shared_Event_MeleeHit,
		Data
	);
	//IllusionDebug::Print(TEXT("_007"));

	//-End
}

void UHeroCombatComponent::OnWeaponPulledFromActor(AActor* InteractedActor)
{

}
