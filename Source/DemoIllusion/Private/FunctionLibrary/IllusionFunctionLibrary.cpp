// A game demo used as a submission__Author Yan Wei.


#include "FunctionLibrary/IllusionFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/IllusionAbilitySystemComponent.h"

#include "Interfaces/PawnCombatInterface.h"

UIllusionAbilitySystemComponent* UIllusionFunctionLibrary::NativeGetIllusionASCFromActor(AActor* InActor)
{
	check(InActor);
	//��������Ա�ϲ�������ϵͳ�����������������ָ��IllusionCharacterBase����Ѱָ��ASC����δ�ҵ���ʹ��AbilitySystemInterface����˵��������
	return CastChecked<UIllusionAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));

}

bool UIllusionFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UIllusionAbilitySystemComponent* ASC = NativeGetIllusionASCFromActor(InActor);
	
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

UPawnCombatComponent* UIllusionFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

void UIllusionFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UIllusionAbilitySystemComponent* ASC = NativeGetIllusionASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}

}

void UIllusionFunctionLibrary::RemoveGameplayTagToActorFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UIllusionAbilitySystemComponent* ASC = NativeGetIllusionASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

void UIllusionFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EIllusionConfrimType& OutConfrimType)
{
	OutConfrimType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EIllusionConfrimType::Yes : EIllusionConfrimType::No;
}

UPawnCombatComponent* UIllusionFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EIllusionValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EIllusionValidType::Valid : EIllusionValidType::Invalid;

	return CombatComponent;
}
