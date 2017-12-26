// Copyright. Aaron Cayabyab 2017.

#pragma once

#include "CoreMinimal.h"
#include "PuzzlePlatformGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API ALobbyGameMode : public APuzzlePlatformGameMode
{
	GENERATED_BODY()

public:

	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	virtual void Logout(AController* Exiting) override;

private:
	uint32 PlayerCount = 0;
	
	
};
