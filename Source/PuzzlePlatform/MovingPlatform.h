// Aaron Cayabyab 2017.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		float Speed = 20.f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget=true))
		FVector TargetLocation;

	void AddActiveTrigger();
	void RemoveActiveTrigger();


protected:

	virtual void BeginPlay() override;

private:
	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;
};
