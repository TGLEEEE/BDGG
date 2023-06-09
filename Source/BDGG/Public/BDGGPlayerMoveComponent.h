// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BDGGPlayerMoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BDGG_API UBDGGPlayerMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBDGGPlayerMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInput(class UInputComponent* PlayerInputComponent);

	UPROPERTY()
	class ABDGGPlayer* me;


	void OnAxisHorizontal(float value);
	void OnAxisVertical(float value);
	void OnAxisLookUp(float value);
	void OnAxisTurnRight(float value);
	void OnActionJump();
	void OnActionRunPressed();
	void OnActionRunReleased();


	float speedRun = 600; // LShift : Run(600)
	float speedWalk = 400; // None : Walk(400)
	float speedCrouch = 200; // LCtrl : Crouch(200)

	FVector direction;
	float walkSpeed = 600;

};
