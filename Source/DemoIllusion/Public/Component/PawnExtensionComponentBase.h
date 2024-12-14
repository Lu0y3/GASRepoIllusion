// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMOILLUSION_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()


protected:
	//helperfuntion
	template<class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T',Template Parameter get GetPawn must be Derived from APawn"); //在编译时进行类型检查，确保 T 是从 APawn 派生的类型。
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template<class T>
	T* GetOwningController()const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T',Template Parameter get GetController must be Derived from AController"); //在编译时进行类型检查，确保 T 是从 APawn 派生的类型。
		return GetOwningPawn<APawn>()->GetController<T>();
	}
	//也可以通过模板函数获取GameMode \ GameInstance \ playerstate ...

		
};
