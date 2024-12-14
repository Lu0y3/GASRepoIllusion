// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IllusionWeaponBase.generated.h"

class UBoxComponent;

//传递一个自定义委托事件给CombatComponent
DECLARE_DELEGATE_OneParam(FOnTargetInteractedDatagate,AActor*)

UCLASS()
class DEMOILLUSION_API AIllusionWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIllusionWeaponBase();

	//委托实例用于OnWeaponCollisionBoxBeginOverlap和OnWeaponCollisionBoxEndOverlap
	FOnTargetInteractedDatagate OnWeaponHitTarget;
	FOnTargetInteractedDatagate OnWeaponPulledFromTarget;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Illusion|Weapon")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Illusion|Weapon")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;

	//-Begin PrimitiveComponent.h  __coo
	//玩家武器的BoxComp_overlap检测
	UFUNCTION()
	virtual void OnWeaponCollisionBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnWeaponCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//-End

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBoxComponent()const { return WeaponCollisionBox; }
};
