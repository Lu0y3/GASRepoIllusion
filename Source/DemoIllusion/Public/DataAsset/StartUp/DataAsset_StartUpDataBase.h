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
	//��StartUpData����ASC
	virtual void GiveToAbilitySystemComponent(UIllusionAbilitySystemComponent* InIllusionASCToGive, int32 ApplyLevel = 1);

protected:
	//�����������
	UPROPERTY(EditDefaultsOnly, Category = "Illusion|StartUpData")
	TArray < TSubclassOf < UIllusionGameplayAbility >> ActivateOnGivenAbilities; 

	UPROPERTY(EditDefaultsOnly, Category = "Illusion|StartUpData")
	TArray < TSubclassOf < UIllusionGameplayAbility >> ReactiveAbilities;

	//����StartUpData��ѡ������������ASC Ȼ�󼤻� OnGivenAbility()����
	void GrantAbilities(const TArray < TSubclassOf < UIllusionGameplayAbility >>& InAbilitiesToGive, UIllusionAbilitySystemComponent* InIllusionASCToGive, int32 ApplyLevel = 1);

	
	//����Ч��GameplayEffec 
	UPROPERTY(EditDefaultsOnly, Category = "Illusion|StartUpData")
	TArray < TSubclassOf <  UGameplayEffect >> StartUpGameplayEffect;
};
