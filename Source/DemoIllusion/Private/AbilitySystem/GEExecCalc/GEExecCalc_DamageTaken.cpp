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
		//S P T B  ��Χ ������ ���� bool
		DEFINE_ATTRIBUTE_CAPTUREDEF(UIllusionAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UIllusionAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UIllusionAttributeSet, DamageTaken, Target, false)
	}
};
//����Source�Լ�ʱ��Ҫ����һ��static
static const FIllusionDamageCapture& GetIllusionDamageCapture()
{
	static FIllusionDamageCapture IllusionDamageCapture;
	return IllusionDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	//��������Բ�������ӵ� RelevantAttributesToCapture �б��У�Ŀ������ִ�� �Զ�����ϷЧ�� ����ʱ������Щ���ԡ�
	// RelevantAttributesToCapture ��һ�� TArray<FGameplayEffectAttributeCaptureDefinition>������ָ����ǰЧ��ִ��ʱ��Ҫ������������ԡ�
	RelevantAttributesToCapture.Add(GetIllusionDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetIllusionDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetIllusionDamageCapture().DamageTakenDef);

	/* Slow way of doing capture ��������
	FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
		UIllusionAttributeSet::StaticClass(),
		GET_MEMBER_NAME_CHECKED(UIllusionAttributeSet , AttackPower)
	);

	FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
		AttackPowerProperty,                            // Ҫ���������
		EGameplayEffectAttributeCaptureSource::Source,  // ���Ե�Դ��ͨ���ǡ�Դ����Ŀ�ꡱ  ��������Ŀ��
		false                                          // �Ƿ񲶻�Ŀ�����Եļӳɻ���ɡ�
	);
	RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition); //���飬���ڴ洢�뵱ǰЧ����ص����Բ����塣
	*/
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// ��ȡ��ǰִ�е�EffectSpec--ʹ������������GE���ڵ�UIllusionGameplayAbilityHero::MakeHeroDamageEffectSpecHandle
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	// WarriorHeroGameplayAbility.cpp    make damage Spec handle      
	//EffectSpec.GetContext().GetSourceObject();
	//EffectSpec.GetContext().GetAbility();
	//EffectSpec.GetContext().GetInstigator();
	//EffectSpec.GetContext().GetEffectCauser();

	//��ʼ���ۺ������������ö�����������Ч��ʱ����Ĳ�����
	FAggregatorEvaluateParameters  EvaluateParameters;
	//SourceTags �� TargetTags �Ǵ�Ч����Դ��ʩ���ߣ���Ŀ���ɫ�в���ı�ǩ������Щ��ǩ���԰�������Ч���������Ի���㷽ʽ��
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetIllusionDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);
	/*
 * Attempts to calculate the magnitude of a captured attribute given the specified parameters. Can fail if the gameplay spec doesn't have���Լ������ָ�������Ĳ������ԵĴ�С�������Ϸ�淶û�У����ܻ�ʧ��
 * a valid capture for the attribute. 	 * ���Ե���Ч����
 *
 * @param InCaptureDef	Attribute definition to attempt to calculate the magnitude of  *InCaptureDef ���Զ��峢�Լ���Ĵ�С
 * @param InEvalParams	Parameters to evaluate the attribute under *InEvalParams *���������µĲ���
 * @param OutMagnitude	[OUT] Computed magnitude *OutMagnitude [OUT] ����ķ���
 *
 * @return True if the magnitude was successfully calculated, false if it was not  * ����ɹ���������򷵻� true�����δ�ɹ������򷵻� false
 */
	//bool AttemptCalculateCapturedAttributeMagnitude(const FGameplayEffectAttributeCaptureDefinition & InCaptureDef, const FAggregatorEvaluateParameters & InEvalParams, OUT float& OutMagnitude) const;
	//Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);


	//-Begin  ���������
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
	//�������������ù�����
	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.3f + 1.0f;
		BaseDamage *= DamageIncreasePercentHeavy;
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	//IllusionDebug::Print(TEXT(" FinalDamageDone"), FinalDamageDone);

	if (FinalDamageDone > 0.f)
	{
		//��Ϊ����޸�����Output Modifier����ӵ� OutExecutionOutput �С�
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(  //�޸ļ����Data--ֵ����
				GetIllusionDamageCapture().DamageTakenProperty,  //Ŀ���ɫ�� DamageTaken ���ԣ���ʾ�ܵ����˺�����EGameplayModOp::Override ��ʾֱ�Ӹ��Ǹ����Ե�ֵ��
				EGameplayModOp::Override,  //����ֵ�ķ�ʽ---���ơ���Ѫ֮��Ӧ���ǼӼ�
				FinalDamageDone
			)
		);

	}
}
