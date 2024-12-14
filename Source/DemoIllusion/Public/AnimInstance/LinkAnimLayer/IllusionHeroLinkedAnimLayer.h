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
	//Ϊ���ö�����ӿ����ʵ���ܵõ�������������ԣ�
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UIllusionHeroAnimInstance* GetIllusionHeroAnimInstance()const;
};
