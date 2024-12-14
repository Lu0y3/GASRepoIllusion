// A game demo used as a submission__Author Yan Wei.


#include "AbilitySystem/IllusionAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "FunctionLibrary/IllusionFunctionLibrary.h"
#include "IllusionGameplayTag.h"
#include "IllusionDebugHelper.h"

UIllusionAttributeSet::UIllusionAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentEndurance(1.f);
	InitMaxEndurance(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);

}

void UIllusionAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	//更新目前健康值  广播百分比
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		// PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

	}

	//更新目前体力值  广播百分比
	if (Data.EvaluatedData.Attribute == GetCurrentEnduranceAttribute())
	{
		const float NewCurrentEndurance = FMath::Clamp(GetCurrentEndurance(), 0.f, GetMaxEndurance());

		SetCurrentEndurance(NewCurrentEndurance);

		/*if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentEndurance() / GetMaxEndurance());
		}*/
	}

	//更新健康值
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(
			TEXT("Old Health: %f , Damage Done: %f , NewCurrentHealth: %f"),
			OldHealth,
			DamageDone,
			NewCurrentHealth
		);

		IllusionDebug::Print(DebugString, FColor::Green);

		//TODO:: Notify the UI
		//PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());


		//DO:: Handle Character Death   
		if (GetCurrentHealth() == 0.f)
		{
			UIllusionFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), IllusionGameplayTags::Shared_Status_Dead);

		}
	}
}
