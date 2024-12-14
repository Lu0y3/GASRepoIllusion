// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "StructTypes/IllusionStructTypes.h"
#include "StructTypes/IllusionEnumTypes.h"
#include "IllusionGameplayAbility.generated.h"

class UPawnCombatComponent;
class UIllusionAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UIllusionGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	//-Begin UGameplayAbility
	//Called when the ability is given to an AbilitySystemComponent 当这个游戏能力被给予GiveAbility()一个ASC时调用OnGivenAbility
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);
	//Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server 原生函数，当技能正常或异常结束时调用。如果 bReplicate 设置为 true，则尝试将结局复制到客户端/服务器
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	//-End UGameplayAbility

	//决定一个GA是什么时候什么条件激活
	UPROPERTY(EditDefaultsOnly, Category = "Illusion|GAPolicy")
	EIllusionAbilityActivatePolicy AbilityActivatePolicy = EIllusionAbilityActivatePolicy::OnTriggered;

	//获得攻击组件 ASC
	UFUNCTION(BlueprintPure, Category = "Illusion|ASC|ActorInfo")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo()const;
	UFUNCTION(BlueprintPure, Category = "Illusion|ASC|ActorInfo")
	UIllusionAbilitySystemComponent* GetIllusionAbilitySystemComponentFromActorInfo()const;

	//激活EffectHandle给Target
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHanle);
	UFUNCTION(BlueprintCallable, Category = "Illusion|ASC|ActorInfo", meta = (DisplayName = "Apply Effect Spec Handle To Target", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHanle,EIllusionSuccessType& OutSuccessType);

};
