// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "StructTypes/IllusionStructTypes.h"

#include "IllusionAbilitySystemComponent.generated.h"

/**	ASCϵͳ����⣺
 *  1��Character�಻ֱ�ӵ���GA������ͨ��ASC ��ӵ���GA  ���ƵĻ���AttributeSet�ȡ�
 *  2������һ��GA��Activate Policy��ֱ�Ӹ���OnGiven������ҪOnTriggered����������
 *  3����GA������thisASC�Ľӿ�
 * 
 */
UCLASS()
class DEMOILLUSION_API UIllusionAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	//�������Ƶ㰴�л���  ��HeroCharacter�����ڰ󶨵��á�
	void OnAbilityInputPressed(const FGameplayTag& InputTag);
	void OnAbilityInputReleased(const FGameplayTag& InputTag);


	//����WeaponGA toASC  ��GA��ͼ�пɵ��á�
	UFUNCTION(BlueprintCallable, Category = "Illusion|GA|Weapon", meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilitiesToASC(const TArray<FIllusionAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);
	//�Ƴ�WeaponGa fromASC
	UFUNCTION(BlueprintCallable, Category = "Illusion|GA|Weapon")
	void RemovedGrantedHeroWeaponAbilitiesFromASC(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);  //UPARAM(ref)�����������Ǹ��������


};
