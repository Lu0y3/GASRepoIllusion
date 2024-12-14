// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapon/IllusionWeaponBase.h"
#include "StructTypes/IllusionStructTypes.h"
#include "GameplayAbilitySpecHandle.h"

#include "IllusionWeaponHero.generated.h"

/**
 * 
 */
UCLASS()
class DEMOILLUSION_API AIllusionWeaponHero : public AIllusionWeaponBase
{
	GENERATED_BODY()
	
public:
	//反射到蓝图中
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Illusion|Data|Weapon")
	FIllsuionWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssginGrantedAbilitySpecHandle(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles()const;

private:
	//储存装备武器的GAHandle
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
