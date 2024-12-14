// A game demo used as a submission__Author Yan Wei.


#include "Characters/IllusionCharacterBase.h"
#include "AbilitySystem/IllusionAbilitySystemComponent.h"
#include "AbilitySystem/IllusionAttributeSet.h"
#include "DataAsset/StartUp/DataAsset_StartUpDataBase.h"

#include "IllusionDebugHelper.h"

// Sets default values
AIllusionCharacterBase::AIllusionCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->bReceivesDecals = false;

	IllusionAbilitySystemComponent = CreateDefaultSubobject<UIllusionAbilitySystemComponent>("IllusionAbilitySystemComponent");
	IllusionAttributeSet = CreateDefaultSubobject<UIllusionAttributeSet>("IllusionAttributeSet");

}

UPawnCombatComponent* AIllusionCharacterBase::GetPawnCombatComponent() const
{
	return nullptr;
}

UAbilitySystemComponent* AIllusionCharacterBase::GetAbilitySystemComponent() const
{
	return GetIllusionAbilitySystemComponent();
}

void AIllusionCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IllusionAbilitySystemComponent)
	{
		//*OwnerActor is the actor that logically owns this component.
		//*AvatarActor is what physical actor in the world we are acting on.Usually a Pawn but it could be a Tower, Building, Turret, etc, may be the same as Owner
		IllusionAbilitySystemComponent->InitAbilityActorInfo(this, this); //this动态绑定

		//确保Data不为空，，触发宏断点
		ensure(!StartUpDataAsset.IsNull());
	}
}

