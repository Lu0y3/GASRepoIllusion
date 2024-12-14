// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "GameplayTagContainer.h"
#include "EnhancedInputComponent.h"
#include "StructTypes/IllusionStructTypes.h"

#include "IllusionDebugHelper.h"
#include "IllusionHeroInputComponent.generated.h"
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UIllusionHeroInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InputConfig, const FNativeGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelaxedFunc);
};

template<class UserObject, typename CallbackFunc>
inline void UIllusionHeroInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InputConfig, const FNativeGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InputConfig, TEXT(" UIllusionHeroInputComponent-Input is Null"));

	if (UInputAction* FoundAction = InputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
		IllusionDebug::Print(TEXT("_04 NativeBind"));

	}
}

template<class UserObject, typename CallbackFunc>
inline void UIllusionHeroInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelaxedFunc)
{
	checkf(InputConfig, TEXT(" UIllusionHeroInputComponent-Ability Input is Null"));

	for (const FIllusionInputActionConfig& AbilityInputActionConfig : InputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid())continue;

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputRelaxedFunc, AbilityInputActionConfig.InputTag);

	}

}
