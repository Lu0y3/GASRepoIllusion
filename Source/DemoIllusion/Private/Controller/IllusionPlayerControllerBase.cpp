// A game demo used as a submission__Author Yan Wei.


#include "Controller/IllusionPlayerControllerBase.h"

#if 1
#include "Blueprint/UserWidget.h"
void AIllusionPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	//检查蓝图是否分配绑定
	if (HUDAsset)
	{
		//HUDAsset类创建实例HUD  将HUD显示在窗口上
		HUD = CreateWidget<UUserWidget>(this, HUDAsset);

		if (HUD)
		{
			HUD->AddToViewport();
		}
	}

}
#endif