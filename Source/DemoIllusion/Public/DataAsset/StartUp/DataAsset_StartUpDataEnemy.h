// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartUp/DataAsset_StartUpDataBase.h"

#include "DataAsset_StartUpDataEnemy.generated.h"

class UIllusionGameplayAbilityEnemy;
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UDataAsset_StartUpDataEnemy : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UIllusionAbilitySystemComponent* InIllusionASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Illusion|StartUpData")
	TArray<TSubclassOf<UIllusionGameplayAbilityEnemy>> EnemyCombatAbilities;

};
