// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "Component/Combat/PawnCombatComponent.h"
#include "GameplayTagContainer.h"
#include "HeroCombatComponent.generated.h"

class AIllusionWeaponHero;
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Illusion|Component|CombatHero")
	AIllusionWeaponHero* GetHeroWeaponByTag(FGameplayTag InWeaponTag) const;

	//-Begin  用于Damage计算
	UFUNCTION(BlueprintCallable, Category = "Illusion|Component|CombatHero")
	AIllusionWeaponHero* GetHeroCurrentEquippedWeapon() const;

	//伤害的级别
	UFUNCTION(BlueprintCallable, Category = "Illusion|Component|CombatHero")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel)const;
	//-End

	//重写来自父类的overlap委托调用
	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromActor(AActor* InteractedActor) override;

};
