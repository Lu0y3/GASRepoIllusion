// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartUp/DataAsset_StartUpDataBase.h"
#include "StructTypes/IllusionStructTypes.h"

#include "DataAsset_StartUpDataHero.generated.h"


//USTRUCT(BlueprintType)
//struct FIllusionAbilitySet
//{
//	GENERATED_BODY()
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputTag")
//	FGameplayTag InputTag;
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
//	TSubclassOf<UIllusionGameplayAbility> AbilityToGrant;
//
//	bool IsValid() const;
//};


/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UDataAsset_StartUpDataHero : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
public:
	//开始时将能力Set赋予角色
	virtual void GiveToAbilitySystemComponent(UIllusionAbilitySystemComponent* InIllusionASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Illusion|StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FIllusionAbilitySet> HeroStartUpAbilitySets;

};
