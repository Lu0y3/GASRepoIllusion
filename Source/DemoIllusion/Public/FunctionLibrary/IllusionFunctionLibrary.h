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
	// 搜寻ASC
	static UIllusionAbilitySystemComponent* NativeGetIllusionASCFromActor(AActor* InActor);
	//是否拥有标签
	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	//用接口的CombatComponent
	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);
#pragma endregion

#pragma region BlueprintCallable

	//如果角色没有标签则给它加上
	UFUNCTION(BlueprintCallable,Category = "Illusion|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	//如果角色有标签则移除
	UFUNCTION(BlueprintCallable, Category = "Illusion|FunctionLibrary")
	static void RemoveGameplayTagToActorFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	//ExpandEnumAsExecs="OutConfrimType"：这个 Meta 标记将使得 EIllusionConfrimType 枚举被扩展为多个执行引脚（例如 True 和 False）而不是只传递一个参数。
	UFUNCTION(BlueprintCallable, Category = "Illusion|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfrimType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EIllusionConfrimType& OutConfrimType);

	UFUNCTION(BlueprintCallable, Category = "Illusion|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EIllusionValidType& OutValidType);
#pragma endregion

	 

};
