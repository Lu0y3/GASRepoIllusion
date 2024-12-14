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
	//��������ص����
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnWeaponCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnWeaponCollisionBoxEndOverlap);


}

void AIllusionWeaponBase::OnWeaponCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forggot to assign instigator as the weapon owner:%s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		//TODO: ��������Ĺ������
		if (WeaponOwningPawn != HitPawn)
		{
			//���ί���Ѱ󶨣�������ð󶨵Ļص����������� OtherActor ��Ϊ�������ݸ��ú�����
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
			//IllusionDebug::Print(TEXT("_OnWeaponHitTarget.ExecuteIfBound(OtherActor)"));

		}

		//TODO: AI���������Ĺ���overlap���
	}

}

void AIllusionWeaponBase::OnWeaponCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forggot to assign instigator as the weapon owner:%s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		//TODO: ��������Ĺ������
		if (WeaponOwningPawn != HitPawn)
		{
			//��OtherActor��ί�еĵ�AActor*���а�
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}

		//TODO: AI���������Ĺ���overlap���
	}
}



