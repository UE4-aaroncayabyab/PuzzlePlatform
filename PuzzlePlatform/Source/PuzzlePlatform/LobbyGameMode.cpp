// Copyright. Aaron Cayabyab 2017.

#include "LobbyGameMode.h"
#include "Engine/World.h"



void ALobbyGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	++PlayerCount;

	if (PlayerCount >= 3)
	{
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		bUseSeamlessTravel = true;
		World->ServerTravel("/Game/Maps/Game?listen");
	}
}

void ALobbyGameMode::Logout(AController * Exiting)
{
	Super::Logout(Exiting);
	if (PlayerCount > 0)
	{
		--PlayerCount;
	}
}
