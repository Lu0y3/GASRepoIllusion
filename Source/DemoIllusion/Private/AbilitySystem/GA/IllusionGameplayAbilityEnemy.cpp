// A game demo used as a submission__Author Yan Wei.


#include "AbilitySystem/GA/IllusionGameplayAbilityEnemy.h"
#include "Characters/IllusionEnemyCharacterBase.h"

AIllusionEnemyCharacterBase* UIllusionGameplayAbilityEnemy::GetEnemyCharacterFromActorInfo()
{
	if (!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<AIllusionEnemyCharacterBase>(CurrentActorInfo->AvatarActor);
	}

    return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UIllusionGameplayAbilityEnemy::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
