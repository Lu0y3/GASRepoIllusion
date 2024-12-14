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
	//伤害类型  TODO::剑气伤害类型
	CurrentEquippedWeaponEnergy, //远程武器_剑气
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
	//使用标签注册生成武器
	UFUNCTION(BlueprintCallable, Category = "Illusion|Combat")
	void RegisterSpawnedWeaponByTag(FGameplayTag InWeaponTagToRegister, AIllusionWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	//通过标签获得角色携带的武器
	UFUNCTION(BlueprintCallable, Category = "Illusion|Combat")
	AIllusionWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGetWeapon) const;

	//追踪当前装备武器的Tag ， 可读写是为了手动添加或移除Tag
	UPROPERTY(BlueprintReadWrite, Category = "Illusion|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	//获得橘色目前携带的武器
	UFUNCTION(BlueprintCallable, Category = "Illusion|Combat")
	AIllusionWeaponBase* GetCharacterCurrentCarriedWeapon() const;

#if 1

#if 0
	//剑气
	UFUNCTION(BlueprintCallable, Category = "Illusion|Combat")
	void ToggleWeaponEnergyCollision(bool bShouldEnable, EToggleDamegeType ToggleDamegeType = EToggleDamegeType::CurrentEquippedWeaponEnergy);
#endif
	//武器盒碰撞
	UFUNCTION(BlueprintCallable, Category = "Illusion|Combat")
	void ToggleWeaponCollision(bool bShouldEnable ,EToggleDamegeType ToggleDamegeType = EToggleDamegeType::CurrentEquippedWeapon);

	//触发来自武器类的委托时调用的函数 在子类中Override
	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromActor(AActor* InteractedActor);
protected:
	//储存overlap的对象
	TArray<AActor*> OverlappedActors;
#endif

private:
	//角色携带的武器TMap 用于注册武器Tag
	TMap<FGameplayTag, AIllusionWeaponBase*> CharacterCarriedWeaponMap;
};
