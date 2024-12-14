// A game demo used as a submission__Author Yan Wei.


#include "Component/Combat/PawnCombatComponent.h"
//������ײ��
#include "Items/Weapon/IllusionWeaponBase.h"
#include "Components/BoxComponent.h"

#include "IllusionDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeaponByTag(FGameplayTag InWeaponTagToRegister, AIllusionWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	//�Ƿ��������ǩ��ע��
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("InWeaponTagToRegister"));
	check(InWeaponToRegister);
	//ע������Tag
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	//��ί����һ���ض��Ķ�������ĳ�Ա����������
	//��ί�б�����ʱ�����ð󶨵ĳ�Ա������
	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromActor);
	//IllusionDebug::Print(TEXT("_InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);"));

	//�Ƿ���ΪЯ������
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;

	}
}

AIllusionWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGetWeapon) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGetWeapon))
	{
		//Find����ֵ const*FoundWeapon 
		if (AIllusionWeaponBase* const*FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGetWeapon))
		{
			return *FoundWeapon;
		}


	}

	return nullptr;
}

AIllusionWeaponBase* UPawnCombatComponent::GetCharacterCurrentCarriedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);

}

#if 0
void UPawnCombatComponent::ToggleWeaponEnergyCollision(bool bShouldEnable, EToggleDamegeType ToggleDamegeType)
{
}
#endif

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamegeType ToggleDamegeType)
{
	if (ToggleDamegeType == EToggleDamegeType::CurrentEquippedWeapon)
	{
		AIllusionWeaponBase* WeaponToCollisionToggle = GetCharacterCurrentCarriedWeapon();
		check(WeaponToCollisionToggle);

		if (bShouldEnable)
		{
			//�����ഴ������ײ��   ������ײ���
			WeaponToCollisionToggle->GetWeaponCollisionBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			//IllusionDebug::Print(WeaponToCollisionToggle->GetActorNameOrLabel() + TEXT(" collision enabled"), FColor::Black);
		}
		else
		{
			//�ر���ײ
			WeaponToCollisionToggle->GetWeaponCollisionBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//IllusionDebug::Print(WeaponToCollisionToggle->GetActorNameOrLabel() + TEXT(" collision disenabled"), FColor::Black);

			//��������ײ��ⴢ���Target
			OverlappedActors.Empty();
		}
		
	}
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	//����������д��������������AIEnemy��Hero������ͬ
}

void UPawnCombatComponent::OnWeaponPulledFromActor(AActor* InteractedActor)
{
}

//TODO: Handle body collision boxes 