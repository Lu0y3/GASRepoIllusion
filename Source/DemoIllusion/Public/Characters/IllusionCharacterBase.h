// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"

#include "IllusionCharacterBase.generated.h"

class UAbilitySystemComponent;
class UIllusionAbilitySystemComponent;
class UIllusionAttributeSet;
class UDataAsset_StartUpDataBase;
UCLASS()
class DEMOILLUSION_API AIllusionCharacterBase : public ACharacter , public IAbilitySystemInterface, public IPawnCombatInterface
{
	GENERATED_BODY()

public:

	AIllusionCharacterBase();

	//-Begin IPawnCombatInterface 自定义
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//-End IPawnCombatInterface

	//-Begin IAbilitySystemComponent
	//获得该角色的ASC用于激发被给予的GA
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//-End IAbilitySystemComponent
	
	//-Begin APawn
	//APawn 类的一个虚拟函数，用于在角色（Pawn）被一个新的控制器（AController）控制时执行自定义的行为。这个函数通常在玩家或 AI 控制器控制角色时被调用。
	virtual void PossessedBy(AController* NewController) override;
	//-End APawn
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Illusion|ASC")
	TObjectPtr<UIllusionAbilitySystemComponent> IllusionAbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Illusion|ASC")
	TObjectPtr<UIllusionAttributeSet> IllusionAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Illusion|ASC|Data")
	TSoftObjectPtr< UDataAsset_StartUpDataBase> StartUpDataAsset;

public:
	FORCEINLINE UIllusionAbilitySystemComponent* GetIllusionAbilitySystemComponent()const { return IllusionAbilitySystemComponent; }
	FORCEINLINE UIllusionAttributeSet* GetIllusionAttributeSet()const { return IllusionAttributeSet; }

};
