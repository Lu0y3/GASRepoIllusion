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

	//-Begin IPawnCombatInterface �Զ���
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//-End IPawnCombatInterface

	//-Begin IAbilitySystemComponent
	//��øý�ɫ��ASC���ڼ����������GA
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//-End IAbilitySystemComponent
	
	//-Begin APawn
	//APawn ���һ�����⺯���������ڽ�ɫ��Pawn����һ���µĿ�������AController������ʱִ���Զ������Ϊ���������ͨ������һ� AI ���������ƽ�ɫʱ�����á�
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
