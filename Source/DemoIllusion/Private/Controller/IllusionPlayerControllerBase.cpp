// A game demo used as a submission__Author Yan Wei.


#include "Controller/IllusionPlayerControllerBase.h"

#if 1
#include "Blueprint/UserWidget.h"
void AIllusionPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	//�����ͼ�Ƿ�����
	if (HUDAsset)
	{
		//HUDAsset�ഴ��ʵ��HUD  ��HUD��ʾ�ڴ�����
		HUD = CreateWidget<UUserWidget>(this, HUDAsset);

		if (HUD)
		{
			HUD->AddToViewport();
		}
	}

}
#endif