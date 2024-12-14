// A game demo used as a submission__Author Yan Wei.


#include "Items/Projectile/IllusionProjectileBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"  //添加模块
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AIllusionProjectileBase::AIllusionProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>("ProjectileCollisionBox");
	SetRootComponent(ProjectileCollisionBox);
	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetupAttachment(ProjectileCollisionBox);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(" ProjectileNiagaraComponent");
	ProjectileNiagaraComponent->SetupAttachment(ProjectileCollisionBox);

	//参数之类的可以在子类中设置U变量控制
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 700.f;
	ProjectileMovementComponent->MaxSpeed = 1000.f;
	ProjectileMovementComponent->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 3.f; //存在时间
}

void AIllusionProjectileBase::BeginPlay()
{
}

