// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/IllusionAnimInstanceBase.h"
#include "IllusionCharacterAnimInstance.generated.h"


class AIllusionCharacterBase;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UIllusionCharacterAnimInstance : public UIllusionAnimInstanceBase
{
	GENERATED_BODY()
	
public:
	//-Begin  AnimInterface
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds)override;
	//-End AnimInterface

protected:
	UPROPERTY()
	TObjectPtr<AIllusionCharacterBase> OwningCharacter;
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwningMovementComponent;

public:
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category = "Illusion|AnimData|Locomotion")
	bool bHasAcceleration; //是否有加速 -启动
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Illusion|AnimData|Locomotion")
	float GroundSpeed;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Illusion|AnimData|Locomotion")
	float GroundWalkSpeed; //地面步行速度
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Illusion|AnimData|Locomotion")
	float GroundRunSpeed;  //地面奔跑速度 --用于后面的Run能力激发？？
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Illusion|AnimData|Locomotion")
	float ToggleWalkRunSpeed; //切换步行和奔跑的临界点条件
};
