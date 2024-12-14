// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StructTypes/IllusionEnumTypes.h"

#include "IllusionFunctionLibrary.generated.h"

class UIllusionAbilitySystemComponent;
class UPawnCombatComponent;


/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UIllusionFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

#pragma region NativeCpp
	// ��ѰASC
	static UIllusionAbilitySystemComponent* NativeGetIllusionASCFromActor(AActor* InActor);
	//�Ƿ�ӵ�б�ǩ
	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	//�ýӿڵ�CombatComponent
	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);
#pragma endregion

#pragma region BlueprintCallable

	//�����ɫû�б�ǩ���������
	UFUNCTION(BlueprintCallable,Category = "Illusion|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	//�����ɫ�б�ǩ���Ƴ�
	UFUNCTION(BlueprintCallable, Category = "Illusion|FunctionLibrary")
	static void RemoveGameplayTagToActorFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	//ExpandEnumAsExecs="OutConfrimType"����� Meta ��ǽ�ʹ�� EIllusionConfrimType ö�ٱ���չΪ���ִ�����ţ����� True �� False��������ֻ����һ��������
	UFUNCTION(BlueprintCallable, Category = "Illusion|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfrimType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EIllusionConfrimType& OutConfrimType);

	UFUNCTION(BlueprintCallable, Category = "Illusion|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EIllusionValidType& OutValidType);
#pragma endregion

	 

};
