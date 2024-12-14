// A game demo used as a submission__Author Yan Wei.


#include "AbilitySystem/GA/IllusionGameplayAbilityHero.h"
#include "Characters/IllusionHeroCharacterBase.h"
#include "Controller/IllusionHeroPlayerControllerBase.h"
#include "AbilitySystem/IllusionAbilitySystemComponent.h"

#include "IllusionGameplayTag.h"


AIllusionHeroCharacterBase* UIllusionGameplayAbilityHero::GetHeroCharacterFromActorInfo()
{
    if (!CachedHeroCharacter.IsValid())
    {
        //拥有当前能力的角色的CurrentActorInfo  成员AvatarActor、PlayerController
        CachedHeroCharacter = Cast<AIllusionHeroCharacterBase>(CurrentActorInfo->AvatarActor);
    }

    return CachedHeroCharacter.IsValid() ? CachedHeroCharacter.Get() : nullptr;
}

AIllusionHeroPlayerControllerBase* UIllusionGameplayAbilityHero::GetHeroControllerFromActorInfo()
{
    if (!CachedHeroController.IsValid())
    {
        CachedHeroController = Cast<AIllusionHeroPlayerControllerBase>(CurrentActorInfo->PlayerController);
    }

    return CachedHeroController.IsValid() ? CachedHeroController.Get() : nullptr;
}

UHeroCombatComponent* UIllusionGameplayAbilityHero::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UIllusionGameplayAbilityHero::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
    float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InComboCount)
{
    check(EffectClass);

    //-BeginGE的上下文 ，构建一个完整的 FGameplayEffectSpec，该对象将用于在能力系统中应用一个效果。
    FGameplayEffectContextHandle ContextHandle = GetIllusionAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContextHandle.SetAbility(this);//该效果是由哪一个能力触发的
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());//将源对象（通常是能力的施放者或执行能力的角色）添加到上下文中。
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());// 将能力的施放者（或行为的起源者）添加到上下文中

    FGameplayEffectSpecHandle  EffectSpecHandle = GetIllusionAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec( //，调用 MakeOutgoingSpec 来创建一个 FGameplayEffectSpec。
        EffectClass,
        GetAbilityLevel(),
        ContextHandle
    );
    //-End

    //-Begin  SetByCaller 是一种特殊的机制，允许你在应用 FGameplayEffect 时动态设置某些效果的数值。
    EffectSpecHandle.Data->SetSetByCallerMagnitude(
        IllusionGameplayTags::Shared_SetByCaller_BaseDamage, //类型
        InWeaponBaseDamage  //值--基础伤害
    );

    if (InCurrentAttackTypeTag.IsValid())
    {
        EffectSpecHandle.Data->SetSetByCallerMagnitude(
            InCurrentAttackTypeTag,
            InComboCount //值--连击数
        );
    }
    //这样就知道他的基础伤害和连击数
    //End

    return  EffectSpecHandle;
}
