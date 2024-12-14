// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "IllusionStructTypes.generated.h"


class UInputAction;
class UIllusionGameplayAbility;
class UIllusionHeroLinkedAnimLayer;
class UInputMappingContext;
//能力激活策略  是直接给予Owner还是 需要触发条件
UENUM(BlueprintType)
enum class EIllusionAbilityActivatePolicy : uint8
{
	OnTriggered,
	OnGiven
};

USTRUCT(BlueprintType)
struct FIllusionInputActionConfig
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;

	bool IsValid() const;
	
};


USTRUCT(BlueprintType)
struct FIllusionAbilitySet
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputTag")
	FGameplayTag InputTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UIllusionGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};



USTRUCT(BlueprintType)
struct FIllsuionWeaponData
{
	GENERATED_BODY()
public:
	//在武器上附着动画层接口，让每把武器都可以拥有自己的动画Data
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UIllusionHeroLinkedAnimLayer> WeaponAnimLayerToLink;
	//在武器上附着能力，武器自带的能力
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FIllusionAbilitySet> DefaultWeaponAbilities;
	//输入上下文，，注意覆盖权值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	//武器的基础伤害
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;  //#include "ScalableFloat.h"
};