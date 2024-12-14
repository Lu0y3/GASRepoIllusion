// A game demo used as a submission__Author Yan Wei.


#include "Characters/IllusionEnemyCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAsset/StartUp/DataAsset_StartUpDataBase.h"
#include "IllusionDebugHelper.h"

AIllusionEnemyCharacterBase::AIllusionEnemyCharacterBase()
{
	//AutoPossessAI ������ APawn ���һ����Ա�������������� AI ����Զ����ƽ�ɫ������ֵ��������Ϊ EAutoPossessAI ö���еĲ�ͬѡ��
	//��һ�� AI ��ɫ�������������л��߱���̬���ɣ�����ͨ�� SpawnActor ������ʱ���Զ���ʼ�� AI ���ơ�
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
	//�첽����StartUpData
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
