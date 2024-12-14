// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/IllusionCharacterAnimInstance.h"
#include "IllusionHeroAnimInstance.generated.h"

class AIllusionHeroCharacterBase;
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UIllusionHeroAnimInstance : public UIllusionCharacterAnimInstance
{
	GENERATED_BODY()
public:
	//-Begin  AnimInterface
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds)override;
	//-End   AnimInterface

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Illusion|AnimData|Ref")
	TObjectPtr<AIllusionHeroCharacterBase> OwningCharacterHeroBase;

	//已经进入Idle的时间
	float EnterIdledTime;

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Illusion|AnimData|Locomotion")
	bool bShouldEnterRelaxState = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Illusion|AnimData|Locomotion")
	float EnterRelaxStateTime = 5.f; //进入放松状态的时间点
};
