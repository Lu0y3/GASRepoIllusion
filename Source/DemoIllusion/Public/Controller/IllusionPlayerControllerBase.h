// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IllusionPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMOILLUSION_API AIllusionPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
#if 1
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> HUDAsset;

	UUserWidget* HUD;

protected:
	virtual void BeginPlay() override;
#endif
};
