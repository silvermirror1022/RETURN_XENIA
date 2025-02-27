// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RXInteractionVisibilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent) )
class RETURN_XENIA_API URXInteractionVisibilityComponent : public USceneComponent
{
	GENERATED_BODY()

public:	

	URXInteractionVisibilityComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void SetInteractionVisibility(bool bIsVisible);
public:	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> WidgetComponent;

	UPROPERTY(EditAnywhere, Category = "ParentWidgetBP")
	TSubclassOf<UUserWidget> WidgetClass;
	
};
