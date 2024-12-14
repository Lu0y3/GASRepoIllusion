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
//�����������  ��ֱ�Ӹ���Owner���� ��Ҫ��������
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
	//�������ϸ��Ŷ�����ӿڣ���ÿ������������ӵ���Լ��Ķ���Data
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UIllusionHeroLinkedAnimLayer> WeaponAnimLayerToLink;
	//�������ϸ��������������Դ�������
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FIllusionAbilitySet> DefaultWeaponAbilities;
	//���������ģ���ע�⸲��Ȩֵ
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	//�����Ļ����˺�
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;  //#include "ScalableFloat.h"
};