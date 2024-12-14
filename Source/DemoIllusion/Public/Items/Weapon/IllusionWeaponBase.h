// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IllusionWeaponBase.generated.h"

class UBoxComponent;

//����һ���Զ���ί���¼���CombatComponent
DECLARE_DELEGATE_OneParam(FOnTargetInteractedDatagate,AActor*)

UCLASS()
class DEMOILLUSION_API AIllusionWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIllusionWeaponBase();

	//ί��ʵ������OnWeaponCollisionBoxBeginOverlap��OnWeaponCollisionBoxEndOverlap
	FOnTargetInteractedDatagate OnWeaponHitTarget;
	FOnTargetInteractedDatagate OnWeaponPulledFromTarget;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Illusion|Weapon")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Illusion|Weapon")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;

	//-Begin PrimitiveComponent.h  __coo
	//���������BoxComp_overlap���
	UFUNCTION()
	virtual void OnWeaponCollisionBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnWeaponCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//-End

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBoxComponent()const { return WeaponCollisionBox; }
};
