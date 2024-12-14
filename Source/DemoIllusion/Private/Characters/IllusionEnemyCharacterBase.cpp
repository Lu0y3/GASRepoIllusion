// A game demo used as a submission__Author Yan Wei.


#include "Characters/IllusionEnemyCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAsset/StartUp/DataAsset_StartUpDataBase.h"
#include "IllusionDebugHelper.h"

AIllusionEnemyCharacterBase::AIllusionEnemyCharacterBase()
{
	//AutoPossessAI 属性是 APawn 类的一个成员变量，它定义了 AI 如何自动控制角色。它的值可以设置为 EAutoPossessAI 枚举中的不同选项
	//当一个 AI 角色被放置在世界中或者被动态生成（例如通过 SpawnActor 创建）时，自动开始由 AI 控制。
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	IllusionEnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");


}

UPawnCombatComponent* AIllusionEnemyCharacterBase::GetPawnCombatComponent() const
{
	return IllusionEnemyCombatComponent;
}

void AIllusionEnemyCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void AIllusionEnemyCharacterBase::InitEnemyStartUpData()
{
	if (StartUpDataAsset.IsNull())
	{
		return;
	}
	//异步加载StartUpData
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		StartUpDataAsset.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartUpDataBase* LoadedData = StartUpDataAsset.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(IllusionAbilitySystemComponent);

					//IllusionDebug::Print(TEXT("Enemy Start Up Data Loaded"));

				}
			}
		)
	);

}
