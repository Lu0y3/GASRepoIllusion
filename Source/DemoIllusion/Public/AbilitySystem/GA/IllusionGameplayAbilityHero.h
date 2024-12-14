// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/IllusionGameplayAbility.h"
#include "IllusionGameplayAbilityHero.generated.h"

class AIllusionHeroCharacterBase;
class AIllusionHeroPlayerControllerBase;
class UHeroCombatComponent;
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UIllusionGameplayAbilityHero : public UIllusionGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintPure, Category = "Illusion|ASC|ActorInfo")
	AIllusionHeroCharacterBase* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Illusion|ASC|ActorInfo")
	AIllusionHeroPlayerControllerBase* GetHeroControllerFromActorInfo();

	//TODO: �����չ��������� �繥�������
	UFUNCTION(BlueprintPure, Category = "Illusion|ASC|ActorInfo")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	//Hero��GE�˺�Ȩ��
	UFUNCTION(BlueprintPure, Category = "Illusion|ASC|GE")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InComboCount);

private:
	//Cached  ���ٷ�������
	TWeakObjectPtr<AIllusionHeroCharacterBase> CachedHeroCharacter;
	TWeakObjectPtr<AIllusionHeroPlayerControllerBase> CachedHeroController;
};
