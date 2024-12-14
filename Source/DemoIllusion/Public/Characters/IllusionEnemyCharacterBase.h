// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "Characters/IllusionCharacterBase.h"
#include "IllusionEnemyCharacterBase.generated.h"

class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API AIllusionEnemyCharacterBase : public AIllusionCharacterBase
{
	GENERATED_BODY()

public:
	AIllusionEnemyCharacterBase();
	
	//-Begin IPawnCombatInterface ×Ô¶¨Òå
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//-End IPawnCombatInterface
protected:
	//-Begin APawn -- IllusionCharacterBase
	virtual void PossessedBy(AController* NewController) override;
	//-End APawn

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Illusion|Enemy|Combat")
	TObjectPtr<UEnemyCombatComponent> IllusionEnemyCombatComponent;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return IllusionEnemyCombatComponent; }
};
