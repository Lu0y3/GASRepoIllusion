// A game demo used as a submission__Author Yan Wei.


#include "Component/Combat/PawnCombatComponent.h"
//武器碰撞盒
#include "Items/Weapon/IllusionWeaponBase.h"
#include "Components/BoxComponent.h"

#include "IllusionDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeaponByTag(FGameplayTag InWeaponTagToRegister, AIllusionWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	//是否该武器标签已注册
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("InWeaponTagToRegister"));
	check(InWeaponToRegister);
	//注册武器Tag
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	//将委托与一个特定的对象和它的成员函数关联。
	//当委托被触发时，调用绑定的成员函数。
	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromActor);
	//IllusionDebug::Print(TEXT("_InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);"));

	//是否作为携带武器
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;

	}
}

AIllusionWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGetWeapon) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGetWeapon))
	{
		//Find返回值 const*FoundWeapon 
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
			//武器类创建的碰撞盒   开启碰撞检测
			WeaponToCollisionToggle->GetWeaponCollisionBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			//IllusionDebug::Print(WeaponToCollisionToggle->GetActorNameOrLabel() + TEXT(" collision enabled"), FColor::Black);
		}
		else
		{
			//关闭碰撞
			WeaponToCollisionToggle->GetWeaponCollisionBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//IllusionDebug::Print(WeaponToCollisionToggle->GetActorNameOrLabel() + TEXT(" collision disenabled"), FColor::Black);

			//清除这次碰撞检测储存的Target
			OverlappedActors.Empty();
		}
		
	}
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	//在子类中重写这两个函数，，AIEnemy与Hero有所不同
}

void UPawnCombatComponent::OnWeaponPulledFromActor(AActor* InteractedActor)
{
}

//TODO: Handle body collision boxes 