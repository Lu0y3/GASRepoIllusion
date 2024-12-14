// A game demo used as a submission__Author Yan Wei.

#pragma once

#include "CoreMinimal.h"
#include "Characters/IllusionCharacterBase.h"
#include "GameplayTagContainer.h"
#include "IllusionHeroCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UHeroCombatComponent;
/**
 * 
 */
UCLASS()
class DEMOILLUSION_API AIllusionHeroCharacterBase : public AIllusionCharacterBase
{
	GENERATED_BODY()

public:
	AIllusionHeroCharacterBase();

	//-Begin IPawnCombatInterface 自定义
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//-End IPawnCombatInterface
protected:

	//-Begin APawn -- IllusionCharacterBase
	virtual void PossessedBy(AController* NewController) override;
	//-End APawn

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="IllusionHero|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraSpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IllusionHero|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IllusionHero|Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHeroCombatComponent> HeroCombatComponent;
#pragma endregion

#pragma region Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IllusionHero|DataAsset", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;


	//FInputActionValue  读取IO
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Look_Zoom(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InputTag);
	void Input_AbilityInputReleased(FGameplayTag InputTag);


#pragma endregion

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IllusionHero|Camera|ZoomSpeed", meta = (ClampMin = "0.5", ClampMax = "20", Delta = "0.5"))
	float CameraLookZoomRatio = 5.f;  //鼠标滑轮缩放视野倍率

#pragma region Forceinline
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent()const { return HeroCombatComponent; }

#pragma endregion
};
