// A game demo used as a submission__Author Yan Wei.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/IllusionAttributeSet.h"
#include "IllusionGameplayTag.h"
#include "IllusionDebugHelper.h"

struct FIllusionDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FIllusionDamageCapture()
	{
		//S P T B  范围 属性名 对象 bool
		DEFINE_ATTRIBUTE_CAPTUREDEF(UIllusionAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UIllusionAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UIllusionAttributeSet, DamageTaken, Target, false)
	}
};
//捕获Source自己时需要进行一下static
static const FIllusionDamageCapture& GetIllusionDamageCapture()
{
	static FIllusionDamageCapture IllusionDamageCapture;
	return IllusionDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	//将多个属性捕获定义添加到 RelevantAttributesToCapture 列表中，目的是在执行 自定义游戏效果 计算时捕获这些属性。
	// RelevantAttributesToCapture 是一个 TArray<FGameplayEffectAttributeCaptureDefinition>，用于指定当前效果执行时需要捕获的所有属性。
	RelevantAttributesToCapture.Add(GetIllusionDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetIllusionDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetIllusionDamageCapture().DamageTakenDef);

	/* Slow way of doing capture 捕获属性
	FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
		UIllusionAttributeSet::StaticClass(),
		GET_MEMBER_NAME_CHECKED(UIllusionAttributeSet , AttackPower)
	);

	FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
		AttackPowerProperty,                            // 要捕获的属性
		EGameplayEffectAttributeCaptureSource::Source,  // 属性的源：通常是“源”或“目标”  防御力是目标
		false                                          // 是否捕获目标属性的加成或减成。
	);
	RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition); //数组，用于存储与当前效果相关的属性捕获定义。
	*/
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// 获取当前执行的EffectSpec--使用这个计算类的GE所在的UIllusionGameplayAbilityHero::MakeHeroDamageEffectSpecHandle
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	// WarriorHeroGameplayAbility.cpp    make damage Spec handle      
	//EffectSpec.GetContext().GetSourceObject();
	//EffectSpec.GetContext().GetAbility();
	//EffectSpec.GetContext().GetInstigator();
	//EffectSpec.GetContext().GetEffectCauser();

	//初始化聚合器评估参数该对象用来计算效果时所需的参数。
	FAggregatorEvaluateParameters  EvaluateParameters;
	//SourceTags 和 TargetTags 是从效果的源（施法者）和目标角色中捕获的标签集，这些标签可以帮助决定效果的适用性或计算方式。
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetIllusionDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);
	/*
 * Attempts to calculate the magnitude of a captured attribute given the specified parameters. Can fail if the gameplay spec doesn't have尝试计算给定指定参数的捕获属性的大小。如果游戏规范没有，可能会失败
 * a valid capture for the attribute. 	 * 属性的有效捕获。
 *
 * @param InCaptureDef	Attribute definition to attempt to calculate the magnitude of  *InCaptureDef 属性定义尝试计算的大小
 * @param InEvalParams	Parameters to evaluate the attribute under *InEvalParams *评估属性下的参数
 * @param OutMagnitude	[OUT] Computed magnitude *OutMagnitude [OUT] 计算的幅度
 *
 * @return True if the magnitude was successfully calculated, false if it was not  * 如果成功计算幅度则返回 true，如果未成功计算则返回 false
 */
	//bool AttemptCalculateCapturedAttributeMagnitude(const FGameplayEffectAttributeCaptureDefinition & InCaptureDef, const FAggregatorEvaluateParameters & InEvalParams, OUT float& OutMagnitude) const;
	//Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);


	//-Begin  获得连击数
	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{

		if (TagMagnitude.Key.MatchesTagExact(IllusionGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			//IllusionDebug::Print(TEXT("BaseDamage"), BaseDamage);
		}
    
		if (TagMagnitude.Key.MatchesTagExact(IllusionGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			//IllusionDebug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);

		}

		if (TagMagnitude.Key.MatchesTagExact(IllusionGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			//IllusionDebug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
		}

	}
	//-End


	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetIllusionDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	//IllusionDebug::Print(TEXT("TargetDefensePower"), TargetDefensePower);

	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.1f + 1.0f;
		BaseDamage *= DamageIncreasePercentLight;
	}
	//根据连击数设置攻击力
	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.3f + 1.0f;
		BaseDamage *= DamageIncreasePercentHeavy;
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	//IllusionDebug::Print(TEXT(" FinalDamageDone"), FinalDamageDone);

	if (FinalDamageDone > 0.f)
	{
		//作为输出修改器（Output Modifier）添加到 OutExecutionOutput 中。
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(  //修改计算的Data--值覆盖
				GetIllusionDamageCapture().DamageTakenProperty,  //目标角色的 DamageTaken 属性（表示受到的伤害）。EGameplayModOp::Override 表示直接覆盖该属性的值。
				EGameplayModOp::Override,  //覆盖值的方式---治疗、残血之类应该是加减
				FinalDamageDone
			)
		);

	}
}
