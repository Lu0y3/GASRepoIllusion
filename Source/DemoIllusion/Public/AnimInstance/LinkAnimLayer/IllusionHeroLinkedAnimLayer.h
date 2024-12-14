// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/IllusionAnimInstanceBase.h"
#include "IllusionHeroLinkedAnimLayer.generated.h"

class UIllusionHeroAnimInstance;
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UIllusionHeroLinkedAnimLayer : public UIllusionAnimInstanceBase
{
	GENERATED_BODY()
	
public:
	//为了让动画层接口里的实例能得到对于类里的属性：
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UIllusionHeroAnimInstance* GetIllusionHeroAnimInstance()const;
};
