// A game demo used as a submission__Author Yan Wei.


#include "AbilitySystem/IllusionGameplayAbility.h"
#include "AbilitySystem/IllusionAbilitySystemComponent.h"
#include "Component/Combat/PawnCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UIllusionGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo,Spec);
	
	//如果被给予的这个能力的激活策略时OnGiven则直接激活
	if (AbilityActivatePolicy == EIllusionAbilityActivatePolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			//OnGivenABility Called when the ability is given to an AbilitySystemComponent  这个ASC有着GA的Spec
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}

}

void UIllusionGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	//直接OnGiven的能力将被直接解除
	if (AbilityActivatePolicy == EIllusionAbilityActivatePolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}

}

UPawnCombatComponent* UIllusionGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	// GetAvatarActorFromActorInfo() from GameplayAbility.h
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();


}

UIllusionAbilitySystemComponent* UIllusionGameplayAbility::GetIllusionAbilitySystemComponentFromActorInfo() const
{
	return Cast<UIllusionAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UIllusionGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, 
	const FGameplayEffectSpecHandle& InSpecHanle)
{

//#include "AbilitySystemBlueprintLibrary.h"获得目标的ASC并把Spec Handle交给目标ASC
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	check(TargetASC);

	return GetIllusionAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHanle.Data,
		TargetASC
	);

}

FActiveGameplayEffectHandle UIllusionGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHanle, EIllusionSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHanle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EIllusionSuccessType::Successful : EIllusionSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}
