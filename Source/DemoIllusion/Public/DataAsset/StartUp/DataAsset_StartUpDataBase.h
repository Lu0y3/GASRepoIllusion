// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UIllusionAbilitySystemComponent;
class UIllusionGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
public:
	//把StartUpData给予ASC
	virtual void GiveToAbilitySystemComponent(UIllusionAbilitySystemComponent* InIllusionASCToGive, int32 ApplyLevel = 1);

protected:
	//激活给定能力
	UPROPERTY(EditDefaultsOnly, Category = "Illusion|StartUpData")
	TArray < TSubclassOf < UIllusionGameplayAbility >> ActivateOnGivenAbilities; 

	UPROPERTY(EditDefaultsOnly, Category = "Illusion|StartUpData")
	TArray < TSubclassOf < UIllusionGameplayAbility >> ReactiveAbilities;

	//把在StartUpData中选择的能力类给于ASC 然后激活 OnGivenAbility()函数
	void GrantAbilities(const TArray < TSubclassOf < UIllusionGameplayAbility >>& InAbilitiesToGive, UIllusionAbilitySystemComponent* InIllusionASCToGive, int32 ApplyLevel = 1);

	
	//技能效果GameplayEffec 
	UPROPERTY(EditDefaultsOnly, Category = "Illusion|StartUpData")
	TArray < TSubclassOf <  UGameplayEffect >> StartUpGameplayEffect;
};
