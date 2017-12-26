// Aaron Cayabyab 2017.

#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"

const static FName SESSION_NAME = TEXT("My Session Game");

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;
	InGameMenuClass = InGameMenuBPClass.Class;
}

void UPuzzlePlatformGameInstance::Init()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Subsystem: %s"), *Subsystem->GetSubsystemName().ToString());

		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnJoinSessionComplete);
			
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Subsystem found"));
	}
}

void UPuzzlePlatformGameInstance::LoadStartMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::LoadInGameMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;
	InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::Host()
{
	if (SessionInterface.IsValid()) {
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else {
			CreateSession();
		}
	}
}

void UPuzzlePlatformGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not create Session"));
		return;
	}

	if (Menu != nullptr)
	{
		Menu->Teardown();
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString("Hosting"));
	}

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	//After session destroyed, re-create new session
	if (Success)
	{
		CreateSession();
	}

}

void UPuzzlePlatformGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UPuzzlePlatformGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid()) {
		//SessionSearch->bIsLanQuery = true;
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		UE_LOG(LogTemp, Warning, TEXT("Searching for sesssions"));
	}
}
void UPuzzlePlatformGameInstance::OnFindSessionsComplete(bool Success)
{
	if (Success  && SessionSearch.IsValid() && Menu != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finished searching for sessions"));

		TArray<FString> ServerNames;
		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Sessions %s"), *SearchResult.GetSessionIdStr());

			ServerNames.Add(SearchResult.GetSessionIdStr());
		}
		Menu->SetServerList(ServerNames);
	}
}


void UPuzzlePlatformGameInstance::Join(uint32 Index)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);

}

void UPuzzlePlatformGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) return;

	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string. "));
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Blue, FString::Printf(TEXT("Joining: %s"), *Address));
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel("/Game/MenuSystem/Menu", ETravelType::TRAVEL_Absolute);
}



