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
	//-Begin  将来自武器类传过来的OtherActor _Tarry
	if (OverlappedActors.Contains(HitActor))
	{
		//IllusionDebug::Print(TEXT("_005"));

		return;
	}
	/*需要在overlap结束的时候清除，，最好的位置是在父类的结束检测的位置清除*/
	OverlappedActors.AddUnique(HitActor);
	IllusionDebug::Print(TEXT("Hero Combat OverlapTarget!"));

	//-End

	//-Begin 发送事件标签给Actor，可以在Hero蓝图中知道具体的HitActor
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
