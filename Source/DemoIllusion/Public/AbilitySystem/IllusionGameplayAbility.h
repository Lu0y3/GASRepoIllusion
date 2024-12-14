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
	//Called when the ability is given to an AbilitySystemComponent �������Ϸ����������GiveAbility()һ��ASCʱ����OnGivenAbility
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);
	//Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server ԭ���������������������쳣����ʱ���á���� bReplicate ����Ϊ true�����Խ���ָ��Ƶ��ͻ���/������
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	//-End UGameplayAbility

	//����һ��GA��ʲôʱ��ʲô��������
	UPROPERTY(EditDefaultsOnly, Category = "Illusion|GAPolicy")
	EIllusionAbilityActivatePolicy AbilityActivatePolicy = EIllusionAbilityActivatePolicy::OnTriggered;

	//��ù������ ASC
	UFUNCTION(BlueprintPure, Category = "Illusion|ASC|ActorInfo")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo()const;
	UFUNCTION(BlueprintPure, Category = "Illusion|ASC|ActorInfo")
	UIllusionAbilitySystemComponent* GetIllusionAbilitySystemComponentFromActorInfo()const;

	//����EffectHandle��Target
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHanle);
	UFUNCTION(BlueprintCallable, Category = "Illusion|ASC|ActorInfo", meta = (DisplayName = "Apply Effect Spec Handle To Target", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHanle,EIllusionSuccessType& OutSuccessType);

};
