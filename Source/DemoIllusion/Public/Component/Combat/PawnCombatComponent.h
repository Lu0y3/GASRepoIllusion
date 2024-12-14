// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"

#include "PawnCombatComponent.generated.h"


class AIllusionWeaponBase;

UENUM(BlueprintType)
enum  class EToggleDamegeType : uint8
{
	//�˺�����  TODO::�����˺�����
	CurrentEquippedWeaponEnergy, //Զ������_����
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	//ʹ�ñ�ǩע����������
	UFUNCTION(BlueprintCallable, Category = "Illusion|Combat")
	void RegisterSpawnedWeaponByTag(FGameplayTag InWeaponTagToRegister, AIllusionWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	//ͨ����ǩ��ý�ɫЯ��������
	UFUNCTION(BlueprintCallable, Category = "Illusion|Combat")
	AIllusionWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGetWeapon) const;

	//׷�ٵ�ǰװ��������Tag �� �ɶ�д��Ϊ���ֶ���ӻ��Ƴ�Tag
	UPROPERTY(BlueprintReadWrite, Category = "Illusion|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	//�����ɫĿǰЯ��������
	UFUNCTION(BlueprintCallable, Category = "Illusion|Combat")
	AIllusionWeaponBase* GetCharacterCurrentCarriedWeapon() const;

#if 1

#if 0
	//����
	UFUNCTION(BlueprintCallable, Category = "Illusion|Combat")
	void ToggleWeaponEnergyCollision(bool bShouldEnable, EToggleDamegeType ToggleDamegeType = EToggleDamegeType::CurrentEquippedWeaponEnergy);
#endif
	//��������ײ
	UFUNCTION(BlueprintCallable, Category = "Illusion|Combat")
	void ToggleWeaponCollision(bool bShouldEnable ,EToggleDamegeType ToggleDamegeType = EToggleDamegeType::CurrentEquippedWeapon);

	//���������������ί��ʱ���õĺ��� ��������Override
	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromActor(AActor* InteractedActor);
protected:
	//����overlap�Ķ���
	TArray<AActor*> OverlappedActors;
#endif

private:
	//��ɫЯ��������TMap ����ע������Tag
	TMap<FGameplayTag, AIllusionWeaponBase*> CharacterCarriedWeaponMap;
};
