// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/IllusionGameplayAbility.h"
#include "IllusionGameplayAbilityEnemy.generated.h"

class AIllusionEnemyCharacterBase;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UIllusionGameplayAbilityEnemy : public UIllusionGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Illusion|Enemy|GA")
	AIllusionEnemyCharacterBase* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Illusion|Enemy|GA")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AIllusionEnemyCharacterBase> CachedEnemyCharacter;
};
