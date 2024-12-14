// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "StructTypes/IllusionStructTypes.h"

#include "IllusionAbilitySystemComponent.generated.h"

/**	ASC系统的理解：
 *  1、Character类不直接调用GA，而是通过ASC 间接调用GA  类似的还有AttributeSet等。
 *  2、分析一个GA的Activate Policy是直接赋予OnGiven还是需要OnTriggered激发条件。
 *  3、在GA类中用thisASC的接口
 * 
 */
UCLASS()
class DEMOILLUSION_API UIllusionAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	//用于类似点按切换的  （HeroCharacter中用于绑定调用、
	void OnAbilityInputPressed(const FGameplayTag& InputTag);
	void OnAbilityInputReleased(const FGameplayTag& InputTag);


	//赋予WeaponGA toASC  （GA蓝图中可调用、
	UFUNCTION(BlueprintCallable, Category = "Illusion|GA|Weapon", meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilitiesToASC(const TArray<FIllusionAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);
	//移除WeaponGa fromASC
	UFUNCTION(BlueprintCallable, Category = "Illusion|GA|Weapon")
	void RemovedGrantedHeroWeaponAbilitiesFromASC(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);  //UPARAM(ref)告诉引擎这是个输入参数


};
