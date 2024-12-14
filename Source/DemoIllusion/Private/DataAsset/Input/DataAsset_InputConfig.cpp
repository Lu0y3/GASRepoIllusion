// A game demo used as a submission__Author Yan Wei.


#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "StructTypes/IllusionStructTypes.h"

#include "IllusionDebugHelper.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
    for (const FIllusionInputActionConfig& InputAction : NativeInputActions)
    {
        if (InputAction.InputTag == InInputTag && InputAction.InputAction)
        {
           // IllusionDebug::Print(TEXT("_05 FindIAByTag"));

            return InputAction.InputAction;

        }
    }

    return nullptr;
}
