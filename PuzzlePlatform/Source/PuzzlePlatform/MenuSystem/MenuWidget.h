// Copyright. Aaron Cayabyab 2017.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuWidget.generated.h"


/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();

	void Teardown();

protected:
	IMenuInterface* MenuInterface;
	
	
	
	
};
