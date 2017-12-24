// Aaron Cayabyab 2017.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UPuzzlePlatformGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPuzzlePlatformGameInstance	(const FObjectInitializer & ObjectInitializer);
	
	virtual void Init();
	
	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);

private:
	 TSubclassOf<class UUserWidget> MenuClass;
	
};
