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
        //ӵ�е�ǰ�����Ľ�ɫ��CurrentActorInfo  ��ԱAvatarActor��PlayerController
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

    //-BeginGE�������� ������һ�������� FGameplayEffectSpec���ö�������������ϵͳ��Ӧ��һ��Ч����
    FGameplayEffectContextHandle ContextHandle = GetIllusionAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContextHandle.SetAbility(this);//��Ч��������һ������������
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());//��Դ����ͨ����������ʩ���߻�ִ�������Ľ�ɫ����ӵ��������С�
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());// ��������ʩ���ߣ�����Ϊ����Դ�ߣ���ӵ���������

    FGameplayEffectSpecHandle  EffectSpecHandle = GetIllusionAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec( //������ MakeOutgoingSpec ������һ�� FGameplayEffectSpec��
        EffectClass,
        GetAbilityLevel(),
        ContextHandle
    );
    //-End

    //-Begin  SetByCaller ��һ������Ļ��ƣ���������Ӧ�� FGameplayEffect ʱ��̬����ĳЩЧ������ֵ��
    EffectSpecHandle.Data->SetSetByCallerMagnitude(
        IllusionGameplayTags::Shared_SetByCaller_BaseDamage, //����
        InWeaponBaseDamage  //ֵ--�����˺�
    );

    if (InCurrentAttackTypeTag.IsValid())
    {
        EffectSpecHandle.Data->SetSetByCallerMagnitude(
            InCurrentAttackTypeTag,
            InComboCount //ֵ--������
        );
    }
    //������֪�����Ļ����˺���������
    //End

    return  EffectSpecHandle;
}
