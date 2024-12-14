// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/IllusionAbilitySystemComponent.h"

#include "IllusionAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DEMOILLUSION_API UIllusionAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UIllusionAttributeSet();

	//Called just after a GameplayEffect is executed to modify the base value of an attribute.
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Illusion|Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UIllusionAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Illusion|Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UIllusionAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Illusion|Endurance")
	FGameplayAttributeData CurrentEndurance;
	ATTRIBUTE_ACCESSORS(UIllusionAttributeSet, CurrentEndurance)

	UPROPERTY(BlueprintReadOnly, Category = "Illusion|Endurance")
	FGameplayAttributeData MaxEndurance;
	ATTRIBUTE_ACCESSORS(UIllusionAttributeSet, MaxEndurance)

	UPROPERTY(BlueprintReadOnly, Category = "Illusion|Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UIllusionAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "Illusion|Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UIllusionAttributeSet, DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "Illusion|Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UIllusionAttributeSet, DamageTaken)

};
