// A game demo used as a submission__Author Yan Wei.


#include "Items/Weapon/IllusionWeaponBase.h"
#include "Components/BoxComponent.h"

#include "IllusionDebugHelper.h"

// Sets default values
AIllusionWeaponBase::AIllusionWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
	
	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>("WeaponCollisionBox");
	WeaponCollisionBox->SetupAttachment(WeaponMesh);
	WeaponCollisionBox->SetBoxExtent(FVector(32.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//处理盒体重叠检测
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnWeaponCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnWeaponCollisionBoxEndOverlap);


}

void AIllusionWeaponBase::OnWeaponCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forggot to assign instigator as the weapon owner:%s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		//TODO: 玩家武器的攻击检测
		if (WeaponOwningPawn != HitPawn)
		{
			//如果委托已绑定，它会调用绑定的回调函数，并将 OtherActor 作为参数传递给该函数。
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
			//IllusionDebug::Print(TEXT("_OnWeaponHitTarget.ExecuteIfBound(OtherActor)"));

		}

		//TODO: AI敌人武器的攻击overlap检测
	}

}

void AIllusionWeaponBase::OnWeaponCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forggot to assign instigator as the weapon owner:%s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		//TODO: 玩家武器的攻击检测
		if (WeaponOwningPawn != HitPawn)
		{
			//将OtherActor与委托的的AActor*进行绑定
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}

		//TODO: AI敌人武器的攻击overlap检测
	}
}



