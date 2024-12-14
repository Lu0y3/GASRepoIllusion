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
	bool bHasAcceleration; //�Ƿ��м��� -����
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Illusion|AnimData|Locomotion")
	float GroundSpeed;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Illusion|AnimData|Locomotion")
	float GroundWalkSpeed; //���沽���ٶ�
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Illusion|AnimData|Locomotion")
	float GroundRunSpeed;  //���汼���ٶ� --���ں����Run������������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Illusion|AnimData|Locomotion")
	float ToggleWalkRunSpeed; //�л����кͱ��ܵ��ٽ������
};
